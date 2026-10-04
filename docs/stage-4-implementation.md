# Linux-Sentinel-X

## Stage 4 – Initial Implementation & Prototype

### 1. Objective

The objective of Stage 4 was to implement the core functionality of Linux-Sentinel-X as a Linux-based system monitoring and process supervision application.

The implementation was developed using C++ and Linux system programming concepts.

The implementation focused on:

- System information collection
- CPU monitoring
- Memory monitoring
- Disk monitoring
- Process monitoring
- Failure detection
- Controlled process recovery
- Recovery attempt limits
- Recovery verification
- Event logging
- Configuration management
- Safe application shutdown
- Integration of all modules

The implementation was kept modular so that each component has a clear responsibility and can be tested independently.

---

## 2. Development Environment

The project was developed and tested in a Linux environment using:

| Component | Technology |
|---|---|
| Programming Language | C++ |
| Operating System | Linux / WSL2 |
| Compiler | GNU C++ |
| Build System | CMake |
| Version Control | Git |
| Repository | GitHub |
| Configuration | Markdown / `.conf` |

The project uses C++17 features and Linux system interfaces for monitoring and process management.

---

## 3. Implemented Components

### 3.1 SystemInfo

**Files:**

```text
include/SystemInfo.h
src/SystemInfo.cpp
```

**Purpose:**

The `SystemInfo` component collects and displays basic information about the Linux system.

It provides information such as:

- Hostname
- Linux kernel version
- CPU information
- Memory information

This information helps provide an overview of the environment in which Linux-Sentinel-X is running.

---

### 3.2 ResourceMonitor

**Files:**

```text
include/ResourceMonitor.h
src/ResourceMonitor.cpp
```

**Purpose:**

The `ResourceMonitor` component monitors important system resource usage.

It monitors:

- CPU usage
- Memory usage
- Disk usage

The monitoring values are collected periodically according to the configured monitoring interval.

The collected values are passed to the monitoring workflow for threshold checking.

---

### 3.3 ProcessMonitor

**Files:**

```text
include/ProcessMonitor.h
src/ProcessMonitor.cpp
```

**Purpose:**

The `ProcessMonitor` component checks whether the configured Linux process is currently running.

The process name is obtained from the configuration file.

The component provides the current process status to the main monitoring workflow.

The possible states include:

- Running
- Not Running

---

### 3.4 ConfigManager

**Files:**

```text
include/ConfigManager.h
src/ConfigManager.cpp
```

**Configuration file:**

```text
config/sentinel.conf
```

**Purpose:**

The `ConfigManager` component reads and provides the monitoring configuration used by the application.

The configuration includes:

- Process name
- Monitoring interval
- CPU threshold
- Memory threshold
- Disk threshold
- Recovery setting

Example configuration:

```text
process_name=testprocess
monitor_interval=5
cpu_threshold=80
memory_threshold=80
disk_threshold=80
recovery_enabled=true
```

Using a configuration file allows monitoring behaviour to be changed without modifying the source code.

---

### 3.5 FailureDetector

**Files:**

```text
include/FailureDetector.h
src/FailureDetector.cpp
```

**Purpose:**

The `FailureDetector` component determines whether a monitored condition has exceeded its configured limit or whether the monitored process has failed.

It checks:

- CPU threshold
- Memory threshold
- Disk threshold
- Process running status

When an abnormal condition is detected, the event is passed to the appropriate logging and recovery logic.

This separates failure detection from the actual recovery operation.

---

### 3.6 RecoveryManager

**Files:**

```text
include/RecoveryManager.h
src/RecoveryManager.cpp
```

**Purpose:**

The `RecoveryManager` component handles controlled recovery of the monitored process.

When the monitored process is detected as not running and recovery is enabled, the component attempts to restart the process.

The recovery mechanism includes:

- Recovery attempt
- Recovery result verification
- Recovery attempt limitation
- Handling of unsuccessful recovery
- Reporting when manual intervention is required

The system does not continuously restart a failed process without limitation. This prevents uncontrolled recovery attempts.

---

### 3.7 Logger

**Files:**

```text
include/Logger.h
src/Logger.cpp
```

**Purpose:**

The `Logger` component records important system monitoring and recovery events.

The log file is:

```text
logs/sentinel.log
```

Events recorded by the logger may include:

- CPU threshold violations
- Memory threshold violations
- Disk threshold violations
- Process failures
- Recovery attempts
- Successful recovery
- Failed recovery
- Recovery being blocked
- Manual intervention requirements

Logging provides a record of important events during system operation.

---

## 4. Main Program Integration

**File:**

```text
src/main.cpp
```

The `main.cpp` file coordinates the different modules and controls the main monitoring workflow.

The overall workflow is:

```text
        Start Application
              |
              v
       Load Configuration
              |
              v
    Display System Information
              |
              v
       Start Monitoring Loop
              |
              v
    Monitor CPU / Memory / Disk
              |
              v
      Monitor Configured Process
              |
              v
       Detect Abnormal Conditions
              |
        +-----+------+
        |            |
        v            v
      Normal       Failure
        |            |
        |            v
        |        Record Event
        |            |
        |            v
        |       Recovery Enabled?
        |         /        \
        |       No          Yes
        |       |            |
        |       v            v
        |     Log       Attempt Recovery
        |                    |
        |                    v
        |              Verify Recovery
        |                    |
        |             +------+------+
        |             |             |
        |           Success       Failure
        |             |             |
        |             v             v
        |           Log      Check Retry Limit
        |                           |
        +---------------------------+
                    |
                    v
             Wait Monitoring Interval
                    |
                    v
              Repeat Monitoring
```

The application continues monitoring until a termination signal is received.

---

## 5. Safe Shutdown

Linux-Sentinel-X includes handling for application termination.

When the application receives a termination signal, the monitoring loop is stopped in a controlled manner.

The shutdown process is designed to:

- Stop further monitoring
- Exit the monitoring loop safely
- Avoid unnecessary operations during termination
- Terminate the application cleanly

This improves the reliability of the long-running monitoring application.

---

## 6. Recovery Control

The recovery mechanism was implemented with controlled retry behaviour.

When a monitored process stops:

1. The process failure is detected.
2. The failure event is logged.
3. The recovery setting is checked.
4. A recovery attempt is performed when recovery is enabled.
5. The process status is checked again.
6. If recovery succeeds, the successful recovery is recorded.
7. If recovery fails, the configured recovery limit is considered.
8. Further automatic recovery is blocked when the retry limit is reached.
9. Manual intervention is reported when automatic recovery cannot continue.

This prevents unlimited automatic restart attempts.

---

## 7. Build System

**File:**

```text
CMakeLists.txt
```

CMake is used to configure and build the project.

The project is compiled using the GNU C++ compiler and C++17.

The project was successfully built using:

```bash
cmake --build build
```

The build generated the Linux-Sentinel-X executable.

The successful build confirmed that the implemented source files and project configuration were correctly integrated.

---

## 8. Initial Prototype Demonstration

The initial working prototype was executed in the Linux environment.

The application successfully demonstrated:

- System information display
- CPU monitoring
- Memory monitoring
- Disk monitoring
- Process monitoring
- Threshold checking
- Failure detection
- Process recovery
- Event logging
- Configuration-based monitoring

Example monitoring output included values such as:

```text
CPU Usage: 0.0313868%
Memory Usage: 7.7303%
Disk Usage: 5.36056%
Process (bash): Running
```

The prototype demonstrated that the major monitoring components were successfully integrated into one working application.

---

## 9. Process Failure and Recovery Demonstration

A temporary test process named `testprocess` was used to verify process monitoring and recovery.

When the process was running, Linux-Sentinel-X detected:

```text
Process (testprocess): Running
```

The process was then intentionally stopped.

The monitoring system detected:

```text
Process (testprocess): Not Running
```

The failure was recorded and the `RecoveryManager` attempted to restart the process.

After successful recovery, the next monitoring cycle detected:

```text
Process (testprocess): Running
```

The demonstrated sequence was:

```text
Running
   ↓
Process stopped
   ↓
Not Running
   ↓
Failure detected
   ↓
Recovery attempted
   ↓
Recovery verified
   ↓
Running
```

This confirmed the basic process supervision and recovery workflow.

---

## 10. Event Logging Demonstration

The logging mechanism was verified during implementation.

Example events recorded by the system include:

```text
Event: Process Failure
Status: Process is not running
Action: Recovery attempted
```

Threshold-related events were also recorded when applicable.

The logging mechanism provides useful information about system conditions and actions taken by the monitoring system.

---

## 11. Git Version Control

The implementation was maintained using Git and pushed to the GitHub repository.

The project repository contains:

- Source code
- Header files
- Configuration files
- Test files
- CMake build configuration
- Stage-wise documentation
- README documentation

The implementation changes were committed to Git during development to maintain project progress and version history.

---

## 12. Implementation Issues and Solutions

During implementation, issues related to monitoring, process recovery and application behaviour were identified and addressed.

The implementation was improved by:

- Separating functionality into independent modules
- Adding controlled recovery attempts
- Verifying recovery results
- Recording failure and recovery events
- Using configuration-based monitoring values
- Handling termination signals safely
- Separating detection and recovery responsibilities
- Improving handling of recovery failure conditions

These changes improved the reliability and maintainability of the application.

---

## 13. Stage 4 Deliverables

The following were completed during Stage 4:

- System information module
- Resource monitoring module
- Process monitoring module
- Configuration management
- Failure detection
- Controlled process recovery
- Recovery verification
- Recovery attempt control
- Event logging
- Safe shutdown handling
- Main application integration
- CMake build configuration
- Working Linux prototype
- Git version control
- Updated project documentation

---

## 14. Stage 4 Status

Stage 4 – Initial Implementation & Prototype was completed successfully.

The core Linux-Sentinel-X application was implemented and integrated into a working monitoring and process supervision system.

The prototype demonstrated system monitoring, process monitoring, failure detection, controlled recovery, recovery verification, event logging and configuration-based operation.

The completed implementation provided the foundation for Stage 5 – Testing, Integration & Improvement.
