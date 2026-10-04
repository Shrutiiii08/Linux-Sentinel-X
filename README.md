# Linux-Sentinel-X

## Linux System Monitoring, Process Supervision and Recovery System

Linux-Sentinel-X is a Linux-based system monitoring and process supervision system developed in **C++**. It continuously monitors important system resources and a configured process, detects abnormal conditions, records failure events, and performs controlled recovery actions.

The project demonstrates **Linux system programming, C++ object-oriented programming, process monitoring, resource monitoring, failure detection, process recovery, configuration management, signal handling, and event logging**.

---

## Project Overview

Linux-Sentinel-X is designed to automatically detect when a monitored process stops running.

Instead of requiring immediate manual intervention, the system:

1. Monitors the configured process.
2. Detects when the process fails.
3. Starts a controlled recovery procedure.
4. Attempts to restart the process within a configured retry limit.
5. Verifies whether recovery was successful.
6. Records the result in the log.
7. Reports **manual intervention required** if recovery cannot be completed.

### Recovery Workflow

```text
              Process Running
                    │
                    ▼
             Continuous Monitoring
                    │
                    ▼
             Process Failure
                    │
                    ▼
             Failure Detection
                    │
                    ▼
          Controlled Recovery
                    │
             ┌──────┴──────┐
             ▼             ▼
       Recovery       Recovery Failed
       Successful           │
             │              ▼
             ▼       Manual Intervention
       Process Running       Required
```

---

## Project Type

**Individual Capstone Project**

## Programming Language

**C++**

## Operating System

**Linux**

---

# Key Features

- CPU usage monitoring
- Memory usage monitoring
- Disk usage monitoring
- Configured process monitoring
- Process failure detection
- Automatic process recovery
- Limited recovery attempts
- Recovery verification
- Manual intervention detection
- Configuration management
- Event logging
- Signal handling
- Linux system information collection
- C++ object-oriented design
- CMake-based build system

---

# System Components

```text
Linux-Sentinel-X
│
├── System Monitoring
│   ├── CPU Usage
│   ├── Memory Usage
│   └── Disk Usage
│
├── Process Monitoring
│   └── Configured Process
│
├── Failure Detection
│   └── Process Failure Detection
│
├── Recovery Management
│   ├── Recovery Attempt
│   ├── Retry Limit
│   └── Recovery Verification
│
├── Configuration Management
│   └── sentinel.conf
│
└── Logging
    └── sentinel.log
```

---

# Project Structure

```text
Linux-Sentinel-X/
│
├── config/
│   └── sentinel.conf
│
├── docs/
│
├── include/
│   ├── ConfigManager.h
│   ├── FailureDetector.h
│   ├── Logger.h
│   ├── RecoveryManager.h
│   └── ...
│
├── src/
│   ├── main.cpp
│   ├── ConfigManager.cpp
│   ├── FailureDetector.cpp
│   ├── Logger.cpp
│   ├── RecoveryManager.cpp
│   └── ...
│
├── tests/
│
├── logs/
│   └── sentinel.log
│
├── CMakeLists.txt
└── README.md
```

---

# Configuration

The monitoring configuration is stored in:

```text
config/sentinel.conf
```

Example configuration:

```ini
process_name=testprocess
monitor_interval=5

cpu_threshold=80
memory_threshold=80
disk_threshold=80

recovery_enabled=true
```

### Configuration Parameters

| Parameter | Purpose |
|---|---|
| `process_name` | Process monitored by Linux-Sentinel-X |
| `monitor_interval` | Time between monitoring cycles |
| `cpu_threshold` | CPU usage warning threshold |
| `memory_threshold` | Memory usage warning threshold |
| `disk_threshold` | Disk usage warning threshold |
| `recovery_enabled` | Enables controlled recovery |

---

# Build

Clone the repository and enter the project directory:

```bash
git clone https://github.com/Shrutiiii08/Linux-Sentinel-X.git
cd Linux-Sentinel-X
```

Create the build directory:

```bash
mkdir -p build
cd build
cmake ..
```

Build the project:

```bash
cmake --build .
```

The executable is generated as:

```text
build/linux-sentinel-x
```

---

# Run

From the project root:

```bash
./build/linux-sentinel-x
```

The program displays system information and continuously monitors the configured process.

Press:

```text
Ctrl+C
```

to stop Linux-Sentinel-X safely.

---

# Evidence and Testing

The project was tested through a functional monitoring and recovery workflow.

The configured test process was intentionally stopped to simulate a process failure.

Linux-Sentinel-X detected the failure and initiated its controlled recovery mechanism.

---

## 1. Normal Monitoring

During normal operation, Linux-Sentinel-X continuously reports system resource usage and process status.

Example:

```text
--- System Status ---

CPU Usage: 0.035%
Memory Usage: 8.02%
Disk Usage: 5.36%
Process (testprocess): Running
```

The monitoring output confirms that:

- CPU usage is being collected.
- Memory usage is being collected.
- Disk usage is being collected.
- The configured process is being monitored.

### Screenshot

Add the normal monitoring screenshot here:

```text
docs/screenshots/normal-monitoring.png
```

Markdown:

```markdown
![Normal Monitoring](docs/screenshots/normal-monitoring.png)
```

---

# 2. Process Failure Detection

To test failure detection, the monitored `testprocess` was intentionally stopped.

Linux-Sentinel-X detected that the process was no longer running:

```text
--- System Status ---

CPU Usage: 0.035%
Memory Usage: 8.02%
Disk Usage: 5.36%
Process (testprocess): Not Running

[WARNING] Process failure detected
[RECOVERY] Starting recovery for: testprocess
```

This demonstrates that the system can detect a monitored process failure without manual monitoring.

### Screenshot

Add the failure detection screenshot here:

```text
docs/screenshots/failure-detection.png
```

Markdown:

```markdown
![Failure Detection](docs/screenshots/failure-detection.png)
```

---

# 3. Automatic Recovery

When the failure was detected, Linux-Sentinel-X started the recovery workflow.

A successful recovery was verified during testing:

```text
[WARNING] Process failure detected

[RECOVERY] Starting recovery for: testprocess
[RECOVERY] Attempt 1/3
[RECOVERY] Stopping process...
[RECOVERY] Starting process...
[VERIFY] Checking process...
[INFO] Recovery successful

Process (testprocess): Running
```

The recovery workflow was:

```text
Process Running
      ↓
Process Stopped
      ↓
Failure Detected
      ↓
Recovery Attempt 1/3
      ↓
Process Restarted
      ↓
Recovery Verified
      ↓
Process Running Again
```

### Screenshot

Add the successful recovery screenshot here:

```text
docs/screenshots/recovery-success.png
```

Markdown:

```markdown
![Recovery Success](docs/screenshots/recovery-success.png)
```

---

# 4. Recovery Retry and Manual Intervention

The system was also tested with the recovery mechanism unable to restart the configured process.

Linux-Sentinel-X correctly limited the recovery attempts to three:

```text
[WARNING] Process failure detected
[RECOVERY] Starting recovery for: testprocess

[RECOVERY] Attempt 1/3
[ERROR] Restart command failed

[RECOVERY] Attempt 2/3
[ERROR] Restart command failed

[RECOVERY] Attempt 3/3
[ERROR] Restart command failed

[ERROR] Recovery limit reached
[ERROR] Manual intervention required
[ERROR] Recovery failed
```

This demonstrates an important safety behavior: the system does **not retry indefinitely**.

Instead, after the configured recovery limit is reached, it reports:

```text
Manual intervention required
```

### Screenshot

Add the manual intervention screenshot here:

```text
docs/screenshots/manual-intervention.png
```

Markdown:

```markdown
![Manual Intervention Required](docs/screenshots/manual-intervention.png)
```

---

# 5. Event Logging

Linux-Sentinel-X records monitoring and recovery events in:

```text
logs/sentinel.log
```

Example log output:

```text
[2026-10-04 06:21:46] [WARNING] Process failure detected | testprocess is not running
[2026-10-04 06:21:46] [RECOVERY] Recovery initiated | Starting controlled recovery
[2026-10-04 06:21:51] [ERROR] Recovery failed | Manual intervention required
```

The log provides a record of:

- Process failures
- Recovery initiation
- Recovery results
- Recovery failures
- Manual intervention requirements
- System shutdown events

View the latest log entries using:

```bash
tail -15 logs/sentinel.log
```

### Screenshot

Add the logging screenshot here:

```text
docs/screenshots/recovery-log.png
```

Markdown:

```markdown
![Recovery Log](docs/screenshots/recovery-log.png)
```

---

# Testing Summary

| Test | Result |
|---|---|
| Project compilation | Passed |
| Linux execution | Passed |
| CPU monitoring | Passed |
| Memory monitoring | Passed |
| Disk monitoring | Passed |
| Process monitoring | Passed |
| Process failure detection | Passed |
| Automatic recovery | Passed |
| Recovery verification | Passed |
| Recovery retry limit | Passed |
| Manual intervention detection | Passed |
| Event logging | Passed |
| Graceful shutdown | Passed |

---

# Development Stages

The project was developed through the following stages:

### Stage 1 — Project Introduction

Defined the objective and scope of Linux-Sentinel-X.

### Stage 2 — Requirements and Development Plan

Identified the required Linux monitoring, process supervision, recovery, configuration, and logging functionality.

### Stage 3 — System Design and Architecture

Designed the project components for monitoring, failure detection, recovery management, configuration handling, and logging.

### Stage 4 — Implementation

Implemented the system using C++ and Linux system interfaces.

### Stage 5 — Testing and Validation

Tested normal monitoring, process failure detection, automatic recovery, recovery failure, retry limits, manual intervention reporting, logging, and graceful shutdown.

---

# Technologies and Concepts

### Programming

- C++
- Object-Oriented Programming
- Classes and modular design
- File handling
- Exception/error handling

### Linux

- Linux system programming
- Process management
- Process monitoring
- `/proc` filesystem
- System information
- Signals
- Process control
- Shell commands

### Build System

- CMake
- GNU C++ compiler

### Monitoring

- CPU usage
- Memory usage
- Disk usage
- Process status
- Configurable thresholds

### Reliability

- Failure detection
- Controlled recovery
- Recovery retry limits
- Recovery verification
- Manual intervention reporting
- Event logging

---

# Why Linux-Sentinel-X?

Traditional monitoring systems may detect failures but still require an administrator to restart failed processes.

Linux-Sentinel-X demonstrates a basic automated supervision approach:

```text
Monitor
   ↓
Detect
   ↓
Recover
   ↓
Verify
   ↓
Log
   ↓
Report
```

The project therefore demonstrates both **monitoring** and **controlled recovery**, rather than only displaying system statistics.

---

# Project Status

**Completed**

- [x] Project introduction
- [x] Requirements documented
- [x] System design documented
- [x] Implementation completed
- [x] CPU monitoring
- [x] Memory monitoring
- [x] Disk monitoring
- [x] Process monitoring
- [x] Failure detection
- [x] Automatic recovery
- [x] Recovery verification
- [x] Recovery retry limit
- [x] Manual intervention reporting
- [x] Event logging
- [x] Testing and validation
- [x] Final CMake build verified

---

# Conclusion

Linux-Sentinel-X successfully demonstrates a Linux-based system monitoring and process supervision workflow.

The system monitors important system resources and a configured process, detects process failures, performs controlled recovery attempts, verifies recovery status, records events through the logging mechanism, and reports when manual intervention is required.

The project demonstrates practical concepts in **Linux system programming, C++, process management, failure detection, recovery management, configuration handling, signal handling, and event logging**.
