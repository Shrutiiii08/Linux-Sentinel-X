# Linux-Sentinel-X

## Stage 3 – System Design & Architecture

### 1. Stage Overview

Stage 3 defines the system architecture, module responsibilities, monitoring workflow, recovery workflow, data structures, class design, and implementation plan for Linux-Sentinel-X.

The design is based on a modular C++ Linux application in which `main.cpp` coordinates system monitoring, process monitoring, failure detection, recovery, configuration, and logging.

The design was kept simple so that each module has a clear responsibility and the complete system remains easy to maintain, test, and explain.

---

## 2. System Architecture

Linux-Sentinel-X follows a modular Linux user-space architecture.

The main components are:

- **SystemInfo** – collects basic system information.
- **ResourceMonitor** – monitors CPU, memory, and disk usage.
- **ProcessMonitor** – checks whether the configured process is running.
- **FailureDetector** – checks resource thresholds and detects process failure.
- **RecoveryManager** – performs controlled recovery attempts.
- **ConfigManager** – loads monitoring and recovery configuration.
- **Logger** – records important system, failure, and recovery events.
- **main.cpp** – coordinates all components and controls the monitoring loop.

### Architecture Flow

```text
                         Linux-Sentinel-X
                                |
                                v
                         +-------------+
                         |   main.cpp  |
                         | Coordinator |
                         +------+------+
                                |
        +-----------------------+-----------------------+
        |                       |                       |
        v                       v                       v
+---------------+       +---------------+       +---------------+
|  ConfigManager|       |  SystemInfo   |       |ResourceMonitor|
+---------------+       +---------------+       +---------------+
        |                       |                       |
        |                       |                CPU / Memory /
        |                       |                   Disk
        |                       |                       |
        +-----------------------+-----------------------+
                                |
                                v
                       +-----------------+
                       | ProcessMonitor  |
                       +--------+--------+
                                |
                                v
                       +-----------------+
                       | FailureDetector |
                       +--------+--------+
                                |
                         Failure detected?
                           /           \
                         No             Yes
                         |               |
                         v               v
                  Continue cycle       Logger
                                         |
                                         v
                                 Recovery enabled?
                                   /          \
                                 No            Yes
                                 |              |
                                 v              v
                              Logger     RecoveryManager
                                                |
                                                v
                                         Recovery attempt
                                                |
                                                v
                                         Verify process
                                                |
                                         +------+------+
                                         |             |
                                      Success        Failure
                                         |             |
                                         v             v
                                      Logger       Retry/Block
                                                       |
                                                       v
                                              Manual intervention
```

---

## 3. Module Responsibilities

| Module | Responsibility |
|---|---|
| `main.cpp` | Coordinates all modules and controls the monitoring cycle |
| `ConfigManager` | Reads process name, thresholds, monitoring interval, and recovery settings |
| `SystemInfo` | Collects basic Linux system information |
| `ResourceMonitor` | Calculates CPU, memory, and disk usage |
| `ProcessMonitor` | Checks whether the configured process is running |
| `FailureDetector` | Detects threshold violations and process failures |
| `RecoveryManager` | Attempts controlled process recovery and verifies the result |
| `Logger` | Records monitoring, failure, recovery, and shutdown events |

Each component performs a specific task. This separation keeps the application modular and makes individual components easier to understand and maintain.

---

## 4. Monitoring Workflow

The application follows a continuous monitoring cycle.

```text
                    Start
                      |
                      v
             Load Configuration
                      |
                      v
              Initialize Modules
                      |
                      v
             Collect System Data
                      |
          +-----------+-----------+
          |                       |
          v                       v
   ResourceMonitor          ProcessMonitor
          |                       |
          +-----------+-----------+
                      |
                      v
              FailureDetector
                      |
                      v
              Check Conditions
                      |
          +-----------+-----------+
          |                       |
        Normal                 Abnormal
          |                       |
          v                       v
   Continue Cycle              Log Event
                                  |
                                  v
                          Recovery Required?
```

The monitoring cycle repeats after the configured monitoring interval.

---

## 5. Resource Monitoring Design

`ResourceMonitor` is responsible for obtaining resource usage information.

The system monitors:

- CPU usage
- Memory usage
- Disk usage

The collected values are passed to the main monitoring workflow and checked against the configured thresholds.

```text
                 Linux System
                      |
                      v
               ResourceMonitor
                      |
          +-----------+-----------+
          |           |           |
          v           v           v
         CPU       Memory        Disk
          |           |           |
          +-----------+-----------+
                      |
                      v
               FailureDetector
                      |
              Compare with limits
                      |
             +--------+--------+
             |                 |
           Normal           Exceeded
             |                 |
             v                 v
       Continue             Log warning
```

---

## 6. Process Monitoring Design

`ProcessMonitor` checks whether the configured process is currently running.

The process name is loaded from:

```text
config/sentinel.conf
```

The process monitoring flow is:

```text
              ConfigManager
                    |
                    v
              Process Name
                    |
                    v
             ProcessMonitor
                    |
                    v
            Is process running?
               /          \
             Yes           No
              |             |
              v             v
         Normal state    FailureDetector
                              |
                              v
                           Logger
```

---

## 7. Failure Detection Design

`FailureDetector` evaluates the information collected by the monitoring components.

It checks:

- CPU threshold
- Memory threshold
- Disk threshold
- Process running status

A resource warning does not automatically mean that the process should be restarted. Process recovery is triggered when the monitored process is detected as failed and recovery is enabled.

```text
CPU Usage --------\
Memory Usage ------> FailureDetector
Disk Usage --------/
Process Status ----/

             |
             v
       Evaluate Conditions
             |
       +-----+------+
       |            |
    Normal        Failure
       |            |
       v            v
 Continue          Log
                  Failure
                     |
                     v
              Recovery Decision
```

---

## 8. Recovery Design

`RecoveryManager` is responsible for controlled recovery of the monitored process.

When a process failure is detected and recovery is enabled:

1. Recovery is initiated.
2. A recovery attempt is performed.
3. The process status is checked again.
4. If the process is running, recovery is considered successful.
5. If recovery fails, another attempt may be performed if attempts remain.
6. If the recovery limit is reached, automatic recovery is blocked.
7. The system reports that manual intervention is required.

### Recovery Flow

```text
              Process Failure
                    |
                    v
             Recovery Enabled?
                /          \
              No            Yes
              |              |
              v              v
        Log warning    Start Recovery
                             |
                             v
                       Attempt Restart
                             |
                             v
                     Verify Process
                       /          \
                    Running     Not Running
                       |             |
                       v             v
                   Success       Retry Available?
                                    /       \
                                  Yes        No
                                   |          |
                                   v          v
                              Retry       Block Recovery
                                              |
                                              v
                                    Manual Intervention
```

---

## 9. Recovery State Handling

The application maintains a recovery-blocking state to prevent repeated automatic recovery after the configured recovery limit has been reached.

When recovery fails repeatedly:

```text
Recovery Attempt
       |
       v
Recovery Failed
       |
       v
Attempts Remaining?
   /            \
 Yes             No
  |               |
  v               v
Retry        recoveryBlocked = true
                  |
                  v
       Manual intervention required
```

When the monitored process is running again, the recovery-blocked state can be reset so that automatic recovery can be enabled again for a future failure.

This prevents unnecessary repeated recovery attempts while allowing the system to recover normally after the process becomes healthy again.

---

## 10. Configuration Design

The configuration is stored in:

```text
config/sentinel.conf
```

The configuration contains values such as:

```text
process_name=testprocess
monitor_interval=5
cpu_threshold=80
memory_threshold=80
disk_threshold=80
recovery_enabled=true
```

The configuration flow is:

```text
             sentinel.conf
                   |
                   v
             ConfigManager
                   |
       +-----------+-----------+
       |           |           |
       v           v           v
    Process     Resource    Recovery
    Settings    Thresholds  Settings
       |           |           |
       +-----------+-----------+
                   |
                   v
             main.cpp
                   |
                   v
            Monitoring Cycle
```

Using a configuration file allows monitoring behaviour to be changed without changing the source code.

---

## 11. Logging Design

The `Logger` component records important events during system operation.

Events include:

- Sentinel startup
- CPU threshold warnings
- Memory threshold warnings
- Disk threshold warnings
- Process failure
- Recovery initiation
- Recovery attempts
- Recovery success
- Recovery failure
- Recovery blocked
- Manual intervention required
- Recovery state reset
- Sentinel shutdown

The logging flow is:

```text
Monitoring
    |
    v
Failure Detection
    |
    v
Recovery
    |
    v
Logger
    |
    v
sentinel.log
```

The log provides a record of the system's behaviour and is also used during testing and validation.

---

## 12. System Information Design

`SystemInfo` provides basic information about the Linux environment.

The information can include:

- CPU information
- Memory information
- Kernel/system information

This information is displayed when Linux-Sentinel-X starts and helps provide the operating environment in which the monitoring system is running.

---

## 13. Data Structures and Configuration Data

The project uses simple structures and class members to store configuration and monitoring information.

### Configuration

```text
Config
├── processName
├── monitorInterval
├── cpuThreshold
├── memoryThreshold
├── diskThreshold
├── recoveryEnabled
├── maxRecoveryAttempts
└── retryDelay
```

### Resource Values

```text
Resource Data
├── CPU Usage
├── Memory Usage
└── Disk Usage
```

### Process State

The monitored process has two primary observed states:

```text
Running
Not Running
```

### Recovery State

The recovery mechanism maintains whether automatic recovery is currently blocked:

```text
Recovery Allowed
       |
       v
Recovery Attempt
       |
       +----> Successful
       |
       +----> Failed
                 |
                 v
          Attempts Exhausted
                 |
                 v
          Recovery Blocked
                 |
                 v
      Manual Intervention Required
```

---

## 14. Class Design

The main classes are organized according to their responsibilities.

```text
                    +-------------+
                    | ConfigManager|
                    +------+------+
                           |
                           v
                    +-------------+
                    |   main.cpp  |
                    +------+------+
                           |
       +-------------------+-------------------+
       |                   |                   |
       v                   v                   v
+--------------+    +--------------+    +--------------+
| SystemInfo   |    |ResourceMonitor|   |ProcessMonitor|
+--------------+    +--------------+    +------+-------+
                                             |
                                             v
                                    +-----------------+
                                    | FailureDetector |
                                    +--------+--------+
                                             |
                                             v
                                    +-----------------+
                                    | RecoveryManager |
                                    +--------+--------+
                                             |
                                             v
                                         +-------+
                                         | Logger|
                                         +-------+
```

### Class Responsibilities

**ConfigManager**
- Loads configuration.
- Provides configuration values to the application.

**SystemInfo**
- Collects system information.

**ResourceMonitor**
- Collects CPU, memory, and disk usage.

**ProcessMonitor**
- Checks the monitored process.

**FailureDetector**
- Checks thresholds.
- Detects process failure.

**RecoveryManager**
- Performs recovery attempts.
- Verifies recovery.
- Handles retry limits.
- Blocks further automatic recovery when required.

**Logger**
- Records system and recovery events.

---

## 15. Sequence Diagram

The main application coordinates the interaction between the modules.

```text
main.cpp        ResourceMonitor   ProcessMonitor   FailureDetector   RecoveryManager   Logger
   |                   |                |                 |                |              |
   |----collect------->|                |                 |                |              |
   |<---resource data--|                |                 |                |              |
   |                   |                |                 |                |              |
   |--------------------------check process-------------> |                |              |
   |<-------------------------process status------------ |                |              |
   |                   |                |                 |                |              |
   |--------------------------------evaluate------------>|                |              |
   |                   |                |                 |                |              |
   |                   |                |                 |                |              |
   |                   |                |          failure detected?      |              |
   |                   |                |                 |                |              |
   |                   |                |                 |----log---------------------->|
   |                   |                |                 |                |              |
   |                   |                |                 |----recover---->|              |
   |                   |                |                 |                |              |
   |                   |                |                 |                |--restart---->|
   |                   |                |                 |                |              |
   |                   |                |                 |<--result-------|              |
   |                   |                |                 |----log---------------------->|
   |                   |                |                 |                |              |
   |<---------------------------continue monitoring--------------------------------------|
```

This sequence reflects the actual design in which `main.cpp` coordinates the monitoring, detection, recovery, and logging components.

---

## 16. State Machine

The monitored process and recovery workflow can be represented using the following states:

```text
                  +-----------+
                  |  STARTING |
                  +-----+-----+
                        |
                        v
                  +-----------+
                  |  RUNNING  |
                  +-----+-----+
                        |
                  Process Stops
                        |
                        v
                  +-----------+
                  |  FAILED   |
                  +-----+-----+
                        |
                 Recovery Enabled
                        |
                        v
                  +-----------+
                  | RECOVERING|
                  +-----+-----+
                        |
                 +------+------+
                 |             |
              Success        Failure
                 |             |
                 v             v
            +---------+   Attempts Remain?
            | RUNNING |       /      \
            +---------+     Yes       No
                              |         |
                              v         v
                           Retry    RECOVERY
                                      BLOCKED
                                        |
                                        v
                              Manual Intervention
```

This state model represents the controlled recovery behaviour implemented in the project.

---

## 17. Error and Failure Handling

The system handles several possible operational conditions:

- Configuration loading failure
- Monitored process not running
- CPU threshold exceeded
- Memory threshold exceeded
- Disk threshold exceeded
- Recovery attempt failure
- Recovery limit reached
- Recovery blocked
- Manual intervention required
- Program termination through `SIGINT` or `SIGTERM`

The recovery system is intentionally limited so that repeated failures do not create an unlimited recovery loop.

---

## 18. Safe Shutdown Design

Linux-Sentinel-X handles `SIGINT` and `SIGTERM`.

When one of these signals is received:

```text
SIGINT / SIGTERM
       |
       v
Signal Handler
       |
       v
Stop Monitoring Loop
       |
       v
Log Shutdown Event
       |
       v
Controlled Program Exit
```

This allows the application to terminate cleanly when the user stops it with `Ctrl+C` or when a termination signal is received.

---

## 19. Project Structure

The project is organized into source code, headers, configuration, documentation, testing, and logs.

```text
Linux-Sentinel-X/
│
├── config/
│   └── sentinel.conf
│
├── docs/
│   ├── stage-1-project-introduction.md
│   ├── stage-2-project-requirements.md
│   ├── stage-3-system-design.md
│   ├── stage-4-implementation.md
│   ├── stage-5-testing-validation.md
│   └── stage-6-final-implementation.md
│
├── include/
│   ├── ConfigManager.h
│   ├── SystemInfo.h
│   ├── ResourceMonitor.h
│   ├── ProcessMonitor.h
│   ├── FailureDetector.h
│   ├── RecoveryManager.h
│   └── Logger.h
│
├── src/
│   ├── ConfigManager.cpp
│   ├── SystemInfo.cpp
│   ├── ResourceMonitor.cpp
│   ├── ProcessMonitor.cpp
│   ├── FailureDetector.cpp
│   ├── RecoveryManager.cpp
│   ├── Logger.cpp
│   └── main.cpp
│
├── tests/
│   └── test_failure.cpp
│
├── logs/
│   └── sentinel.log
│
├── CMakeLists.txt
└── README.md
```

---

## 20. Development and Git Strategy

The project is maintained using Git and GitHub.

The `main` branch contains the current stable project version.

Development changes are recorded through meaningful commits covering implementation, fixes, testing, and documentation.

Examples include:

```text
docs: update project documentation
feat: implement monitoring functionality
feat: implement process recovery
fix: improve recovery handling
test: validate failure and recovery workflow
docs: update README
```

The GitHub repository is used to maintain the source code, documentation, project history, and final submission.

---

## 21. Implementation Plan

The implementation follows the architecture defined in this stage:

1. Configure the project using CMake.
2. Implement configuration loading.
3. Implement system information collection.
4. Implement resource monitoring.
5. Implement process monitoring.
6. Implement failure detection.
7. Implement event logging.
8. Implement controlled process recovery.
9. Add recovery attempt limits.
10. Add recovery blocking and manual intervention handling.
11. Add signal handling and controlled shutdown.
12. Integrate all modules through `main.cpp`.
13. Test the complete monitoring and recovery workflow.
14. Fix identified issues and improve reliability.
15. Complete final documentation.

---

## 22. Stage 3 Outcome

Stage 3 established the technical design of Linux-Sentinel-X before and during implementation.

The system architecture, module responsibilities, monitoring flow, failure detection flow, recovery mechanism, configuration flow, logging design, data structures, class responsibilities, sequence flow, state machine, error handling, safe shutdown, project structure, and Git strategy were defined.

This design provided the foundation for the implementation and testing work completed in the following stages.
