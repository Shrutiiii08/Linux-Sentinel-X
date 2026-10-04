# Linux-Sentinel-X

## Linux System Monitoring, Process Supervision and Controlled Recovery System

Linux-Sentinel-X is a Linux-based system monitoring and process supervision application developed using **C++ and Linux system programming concepts**.

The system continuously monitors selected system resources and a configured Linux process. It detects configured resource threshold violations and process failures, records important events in a log file, and performs controlled recovery when automatic recovery is enabled.

The project was developed as an individual project and follows a structured development process covering **requirements, system design, implementation, testing, validation and finalization**.

---

## 1. Project Objective

The main objective of Linux-Sentinel-X is to provide a simple and reliable Linux monitoring and process supervision mechanism.

The system is designed to:

- Monitor CPU, memory and disk usage.
- Monitor a configured Linux process.
- Detect configured resource threshold violations.
- Detect when the monitored process stops.
- Record important monitoring and recovery events.
- Attempt controlled process recovery when enabled.
- Verify whether recovery was successful.
- Limit repeated recovery attempts.
- Report when manual intervention is required.
- Shut down safely when requested.

---

## 2. Problem Statement

Linux systems continuously run multiple processes and system services. A process may stop unexpectedly or system resources may exceed acceptable limits.

Manually monitoring these conditions continuously is difficult.

Linux-Sentinel-X addresses this problem by providing an automated user-space monitoring and supervision mechanism that periodically checks system resources and a configured process, detects abnormal conditions, records events and performs controlled recovery where applicable.

---

## 3. Key Features

### System Information

The application displays basic Linux system information including:

- Hostname
- Kernel version
- CPU information
- Memory information

### Resource Monitoring

The application monitors:

- CPU usage
- Memory usage
- Disk usage

The monitoring interval is configurable.

### Process Monitoring

A configured Linux process is continuously checked to determine whether it is running.

### Failure Detection

Linux-Sentinel-X detects:

- CPU usage above the configured threshold
- Memory usage above the configured threshold
- Disk usage above the configured threshold
- Monitored process failure

### Controlled Recovery

When the monitored process is not running and automatic recovery is enabled, the system attempts to restart it.

The recovery mechanism includes:

- Recovery attempts
- Recovery verification
- Configurable maximum recovery attempts
- Retry delay
- Recovery blocking after repeated failure
- Manual intervention notification

### Recovery State Handling

When recovery repeatedly fails, automatic recovery is blocked to prevent unlimited restart attempts.

The system reports:

```text
Automatic recovery blocked.
Manual intervention required.
```

When the monitored process becomes available again, the recovery state can be reset and automatic recovery can become available again.

### Event Logging

Important events are recorded in:

```text
logs/sentinel.log
```

Examples include:

- CPU threshold exceeded
- Memory threshold exceeded
- Disk threshold exceeded
- Process failure
- Recovery initiated
- Recovery successful
- Recovery failed
- Recovery blocked
- Manual intervention required
- Sentinel startup
- Sentinel shutdown

### Safe Shutdown

The application handles termination signals such as `SIGINT` and `SIGTERM` and performs a controlled shutdown.

---

## 4. System Workflow

The overall monitoring workflow is:

```text
        Start Linux-Sentinel-X
                  |
                  v
        Load Configuration
                  |
                  v
       Display System Information
                  |
                  v
       Monitor System Resources
        /          |          \
       v           v           v
     CPU        Memory       Disk
        \          |          /
         \         |         /
                  v
        Monitor Configured Process
                  |
                  v
          Detect Conditions
                  |
          +-------+-------+
          |               |
          v               v
     Threshold       Process Failure
      Violation          |
          |              v
          |        Recovery Enabled?
          |          /          \
          |        Yes           No
          |         |             |
          |         v             v
          |    Attempt Recovery  Log Event
          |         |
          |         v
          |    Verify Process
          |       /       \
          |     Yes        No
          |      |          |
          |      v          v
          |   Success   Retry Until Limit
          |                  |
          |                  v
          |          Manual Intervention
          |
          v
       Log Event
          |
          v
   Wait for Monitoring Interval
          |
          v
     Repeat Monitoring
```

---

## 5. Recovery Workflow

The recovery mechanism follows a controlled process:

```text
Process Running
      |
      v
Process Stops
      |
      v
Failure Detected
      |
      v
Recovery Enabled?
      |
     Yes
      |
      v
Recovery Attempt
      |
      v
Check Process
    /     \
  Running  Not Running
    |          |
    v          v
 Success    Retry
               |
               v
       Maximum Attempts?
          /          \
        No            Yes
        |              |
        v              v
   Try Again      Block Recovery
                       |
                       v
             Manual Intervention
```

This prevents the application from repeatedly attempting recovery without a limit.

---

## 6. Configuration

Monitoring settings are stored in:

```text
config/sentinel.conf
```

Example configuration:

```text
process_name=testprocess
monitor_interval=5
cpu_threshold=80
memory_threshold=80
disk_threshold=80
recovery_enabled=true
max_recovery_attempts=3
retry_delay=2
```

### Configuration Parameters

| Parameter | Purpose |
|---|---|
| `process_name` | Process monitored by Linux-Sentinel-X |
| `monitor_interval` | Time between monitoring cycles |
| `cpu_threshold` | Maximum configured CPU usage threshold |
| `memory_threshold` | Maximum configured memory usage threshold |
| `disk_threshold` | Maximum configured disk usage threshold |
| `recovery_enabled` | Enables or disables automatic recovery |
| `max_recovery_attempts` | Maximum number of recovery attempts |
| `retry_delay` | Delay between recovery attempts |

---

## 7. Project Architecture

Linux-Sentinel-X follows a modular architecture.

```text
                    +----------------+
                    |    main.cpp    |
                    |  Coordinator   |
                    +-------+--------+
                            |
       +--------------------+--------------------+
       |          |           |          |       |
       v          v           v          v       v
+-----------+ +----------+ +----------+ +-----+ +--------+
| System    | | Resource | | Process  | |Config| | Logger |
| Info      | | Monitor  | | Monitor  | |Mgr   | |        |
+-----------+ +----------+ +----------+ +-----+ +--------+
       |          |           |
       |          |           v
       |          |    +----------------+
       |          +--->|    Failure     |
       |               |    Detector    |
       |               +-------+--------+
       |                       |
       |                       v
       |               +---------------+
       +-------------->|   Recovery    |
                       |   Manager     |
                       +---------------+
```

### Main Components

| Component | Responsibility |
|---|---|
| `SystemInfo` | Collects and displays basic Linux system information |
| `ResourceMonitor` | Collects CPU, memory and disk usage |
| `ProcessMonitor` | Checks whether the configured process is running |
| `FailureDetector` | Detects threshold violations and process failures |
| `RecoveryManager` | Performs controlled process recovery |
| `Logger` | Records important system and recovery events |
| `ConfigManager` | Loads configuration settings |
| `main.cpp` | Coordinates the complete monitoring workflow |

---

## 8. Project Structure

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
│   └── stage-6-finalization.md
│
├── include/
│   ├── ConfigManager.h
│   ├── FailureDetector.h
│   ├── Logger.h
│   ├── ProcessMonitor.h
│   ├── RecoveryManager.h
│   ├── ResourceMonitor.h
│   └── SystemInfo.h
│
├── src/
│   ├── ConfigManager.cpp
│   ├── FailureDetector.cpp
│   ├── Logger.cpp
│   ├── main.cpp
│   ├── ProcessMonitor.cpp
│   ├── RecoveryManager.cpp
│   ├── ResourceMonitor.cpp
│   └── SystemInfo.cpp
│
├── tests/
│
├── CMakeLists.txt
├── README.md
└── .gitignore
```

---

## 9. Technologies Used

| Category | Technology |
|---|---|
| Programming Language | C++ |
| Operating System | Linux |
| Build System | CMake |
| Compiler | GNU C++ |
| Version Control | Git |
| Repository | GitHub |
| Configuration | Custom configuration file |
| System Interfaces | Linux system interfaces and `/proc` |
| Documentation | Markdown |

---

## 10. Build Instructions

### Step 1 – Clone the Repository

```bash
git clone https://github.com/Shrutiiii08/Linux-Sentinel-X.git
cd Linux-Sentinel-X
```

### Step 2 – Configure the Project

```bash
cmake -S . -B build
```

### Step 3 – Build the Project

```bash
cmake --build build
```

A successful build produces the executable:

```text
build/linux-sentinel-x
```

---

## 11. Running the Application

Run:

```bash
./build/linux-sentinel-x
```

The application loads:

```text
config/sentinel.conf
```

and begins the monitoring loop.

To stop the application safely:

```text
Ctrl + C
```

---

## 12. Example Monitoring Output

A normal monitoring cycle displays information similar to:

```text
--- System Status ---
CPU Usage: XX%
Memory Usage: XX%
Disk Usage: XX%
Process (testprocess): Running
```

If the monitored process stops:

```text
Process (testprocess): Not Running
[WARNING] Process failure detected
```

The recovery mechanism can then attempt to restart the process.

After successful recovery:

```text
[INFO] Recovery successful
Process (testprocess): Running
```

---

## 13. Logging

The application records important events in:

```text
logs/sentinel.log
```

The log can be viewed using:

```bash
tail -n 20 logs/sentinel.log
```

Example event:

```text
Event: Process Failure | Status: Process is not running | Action: Recovery attempted
```

Logging provides a record of system conditions, failures and recovery actions.

---

## 14. Testing and Validation

The project was tested after implementation.

The following areas were validated:

| Test | Result |
|---|---|
| Project compilation | PASS |
| System information | PASS |
| CPU monitoring | PASS |
| Memory monitoring | PASS |
| Disk monitoring | PASS |
| Process monitoring | PASS |
| Resource threshold detection | PASS |
| Process failure detection | PASS |
| Automatic process recovery | PASS |
| Recovery verification | PASS |
| Recovery attempt control | PASS |
| Failure logging | PASS |
| Recovery logging | PASS |
| Configuration handling | PASS |
| Safe shutdown | PASS |

A temporary test process was used during process failure and recovery testing.

The tested recovery sequence was:

```text
Running → Not Running → Recovery Attempt → Running
```

This confirmed the main monitoring, failure detection, recovery and logging workflow.

---

## 15. Recovery Failure and Manual Intervention

The project also handles unsuccessful automatic recovery.

If the configured maximum number of recovery attempts is reached, automatic recovery is blocked.

The system reports:

```text
[ERROR] Recovery limit reached
[ERROR] Manual intervention required
```

This prevents unlimited automatic restart attempts and provides a clear indication that further action is required.

---

## 16. Development Stages

The project was developed through six stages.

### Stage 1 – Project Introduction

Defined:

- Project idea
- Problem statement
- Objectives
- Scope
- Expected outcome
- Application

### Stage 2 – Project Requirements & Development Plan

Defined:

- Functional requirements
- Non-functional requirements
- Project modules
- Project scope
- Acceptance criteria
- Development plan

### Stage 3 – System Design & Architecture

Defined:

- System architecture
- Component responsibilities
- Monitoring workflow
- Recovery workflow
- Data flow
- UML/design documentation
- Implementation plan

### Stage 4 – Initial Implementation

Implemented:

- System information
- Resource monitoring
- Process monitoring
- Configuration management
- Failure detection
- Recovery management
- Logging
- Main monitoring workflow
- CMake build

### Stage 5 – Testing & Improvement

Performed:

- Build verification
- System monitoring testing
- Process monitoring testing
- Failure detection testing
- Recovery testing
- Logging verification
- Configuration testing
- Reliability improvements

### Stage 6 – Finalization

Completed:

- Final implementation review
- Documentation
- Project structure
- Testing validation
- GitHub repository organization
- Final project preparation

---

## 17. Project Scope

### Included

- Linux system monitoring
- CPU monitoring
- Memory monitoring
- Disk monitoring
- Process monitoring
- Threshold detection
- Process failure detection
- Controlled process recovery
- Recovery attempt limits
- Recovery verification
- Manual intervention handling
- Event logging
- Configuration management
- Signal handling
- CMake build system
- Git and GitHub version control
- Stage-wise documentation

### Not Included

- Graphical user interface
- Cloud-based monitoring
- Remote monitoring
- Database-based monitoring
- Email/SMS alerting


The project intentionally focuses on a simple, explainable and modular Linux user-space monitoring and process supervision system.

---

## 18. Limitations

The current version has the following limitations:

- Monitoring is performed locally on the Linux system.
- Only the configured process is supervised.
- Recovery is designed for the configured process rather than arbitrary services.
- There is no graphical interface.
- There is no remote monitoring or centralized dashboard.
- Logging is file-based.
- Recovery depends on the process being restartable in the Linux environment.

---

## 19. Future Improvements

Possible future improvements include:

- Monitoring multiple processes simultaneously.
- Adding a graphical or web-based monitoring dashboard.
- Adding remote monitoring capabilities.
- Adding notification mechanisms.
- Supporting service-specific recovery using Linux service management.
- Adding more detailed performance statistics.
- Improving automated testing and test coverage.
- Adding more advanced fault detection mechanisms.

These improvements are outside the scope of the current implementation.

---

## 20. Learning Outcomes

Through this project, the following concepts were practiced:

- C++ programming
- Object-oriented programming
- Linux system programming
- Process management
- System resource monitoring
- Failure detection
- Process recovery
- File handling
- Configuration management
- Logging
- Signal handling
- Modular software design
- CMake
- Git and GitHub
- Software development lifecycle
- Testing and validation

---

## 21. Capstone Development Process

The project follows the required development process:

```text
Requirements
     ↓
System Design
     ↓
Implementation
     ↓
Testing
     ↓
Improvement
     ↓
Finalization
```

Each stage was documented separately and maintained in the `docs/` directory.

The project also maintained Git version control throughout development.

---

## 22. Repository

GitHub Repository:

**https://github.com/Shrutiiii08/Linux-Sentinel-X**

The repository contains the source code, configuration, documentation and project files required to understand, build and demonstrate Linux-Sentinel-X.

---

## 23. Final Status

**Linux-Sentinel-X – Project Completed**

The project successfully implements a Linux-based system monitoring and process supervision system using C++.

The final system can:

- Monitor system resources
- Monitor a configured process
- Detect abnormal conditions
- Detect process failures
- Log important events
- Attempt controlled process recovery
- Verify recovery
- Limit recovery attempts
- Report when manual intervention is required
- Shut down safely

The project has completed its implementation, testing, documentation and finalization stages and is ready for final demonstration and evaluation.
