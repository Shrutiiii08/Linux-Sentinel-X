# Linux-Sentinel-X

## Linux System Monitoring, Process Supervision and Recovery System

Linux-Sentinel-X is a Linux-based system monitoring and process supervision system developed in C++. It monitors important system resources and a configured process, detects abnormal conditions, records failure events, and performs controlled recovery actions.

The project demonstrates Linux system programming concepts, C++ object-oriented programming, process monitoring, resource monitoring, failure detection, process recovery, configuration management, signal handling, and event logging.

---

## Project Type

**Individual Capstone Project**

### Programming Language
**C++**

### Operating System
**Linux**

---

## Project Objective

Linux-Sentinel-X continuously monitors important system resources and a configured Linux process.

When a process failure is detected, the system:

1. Detects the failure.
2. Initiates controlled recovery.
3. Attempts to restart the configured process.
4. Verifies whether the process has recovered.
5. Retries recovery only within a configured limit.
6. Reports **manual intervention required** when recovery cannot be completed.
7. Records important monitoring, failure, and recovery events in the log.

The objective is to demonstrate a practical Linux process supervision and recovery workflow using C++.

---

## Key Features

- CPU usage monitoring
- Memory usage monitoring
- Disk usage monitoring
- Configured process monitoring
- Process failure detection
- Automatic process recovery
- Recovery attempt limiting
- Recovery verification
- Manual intervention detection
- Configuration management
- Event logging
- Signal handling
- Graceful shutdown
- C++ object-oriented programming
- Linux system programming

---

## System Workflow

```text
        Process Running
              |
              v
      Continuous Monitoring
              |
              v
       Process Failure
          Detected
              |
              v
      Controlled Recovery
              |
              v
       Restart Attempt
              |
              v
       Verify Process
              |
        +-----+-----+
        |           |
        v           v
     Success      Failure
        |           |
        v           v
   Monitoring   Retry Recovery
                   |
              Max Attempts?
                /       \
              No         Yes
              |           |
              v           v
           Retry       Manual
                       Intervention
                        Required
```

---

# Project Structure

```text
Linux-Sentinel-X/
├── config/
│   └── sentinel.conf
├── docs/
├── include/
├── src/
├── tests/
├── logs/
├── CMakeLists.txt
└── README.md
```

---

# Main Components

### System Monitoring

Collects and displays system information including:

- CPU usage
- Memory usage
- Disk usage
- Hostname
- Kernel information
- CPU information

### Process Monitoring

Monitors a configured Linux process and determines whether it is currently running.

### Failure Detection

Detects when the monitored process is no longer running and records the failure event.

### Recovery Manager

Attempts to recover the failed process automatically.

The recovery mechanism uses a controlled number of attempts rather than retrying indefinitely.

### Configuration Manager

Loads monitoring and recovery settings from the configuration file.

### Logger

Records monitoring, warning, recovery, and error events in:

```text
logs/sentinel.log
```

---

# Configuration

The monitoring configuration is stored in:

```text
config/sentinel.conf
```

Example:

```text
process_name=testprocess
monitor_interval=5
cpu_threshold=80
memory_threshold=80
disk_threshold=80
recovery_enabled=true
```

### Configuration Parameters

| Parameter | Description |
|---|---|
| `process_name` | Process that Linux-Sentinel-X monitors |
| `monitor_interval` | Time between monitoring cycles |
| `cpu_threshold` | CPU usage warning threshold |
| `memory_threshold` | Memory usage warning threshold |
| `disk_threshold` | Disk usage warning threshold |
| `recovery_enabled` | Enables or disables automatic recovery |

---

# Build Instructions

Clone the repository and enter the project directory:

```bash
git clone https://github.com/Shrutiiii08/Linux-Sentinel-X.git
cd Linux-Sentinel-X
```

Create the build directory:

```bash
mkdir -p build
cd build
```

Generate the build files:

```bash
cmake ..
```

Build the project:

```bash
cmake --build .
```

The executable will be generated as:

```text
build/linux-sentinel-x
```

---

# Run

From the project root directory:

```bash
./build/linux-sentinel-x
```

The program displays system information and continuously monitors the configured process.

Press:

```text
Ctrl+C
```

to stop Linux-Sentinel-X gracefully.

---

# Testing and Validation

The project was tested using a controlled process-failure workflow.

The configured test process was intentionally stopped to simulate a real process failure.

The system was tested for:

- Normal process monitoring
- Process failure detection
- Automatic recovery
- Recovery verification
- Recovery retry limit
- Manual intervention detection
- Event logging
- Graceful shutdown

---

## 1. Normal Monitoring

During normal operation, Linux-Sentinel-X continuously reports the system status.

Example output:

```text
--- System Status ---
CPU Usage: 0.0353913%
Memory Usage: 8.02777%
Disk Usage: 5.36824%
Process (testprocess): Running
```

The process remains under continuous supervision while system resource information is updated.

---

## 2. Successful Automatic Recovery

The monitored process was intentionally stopped while Linux-Sentinel-X was running.

The system detected the failure and successfully recovered the process.

Example:

```text
--- System Status ---
CPU Usage: 0.0354273%
Memory Usage: 8.05572%
Disk Usage: 5.36824%
Process (testprocess): Not Running

[WARNING] Process failure detected
[RECOVERY] Starting recovery for: testprocess
[RECOVERY] Attempt 1/3
[RECOVERY] Stopping process...
[RECOVERY] Starting process...
[VERIFY] Checking process...
[INFO] Recovery successful
[INFO] Recovery successful
```

After recovery, the process returned to the running state:

```text
--- System Status ---
CPU Usage: 0.0354238%
Memory Usage: 8.04565%
Disk Usage: 5.36824%
Process (testprocess): Running
```

### Recovery Result

```text
Process Running
       |
       v
Process Stopped
       |
       v
Failure Detected
       |
       v
Recovery Attempted
       |
       v
Process Restarted
       |
       v
Recovery Verified
       |
       v
Process Running Again
```

This verifies that Linux-Sentinel-X can automatically detect and recover from a process failure without requiring manual intervention.

---

# 3. Recovery Failure and Manual Intervention

A second test was performed by making the monitored process unavailable so that the recovery command could not successfully restart it.

Linux-Sentinel-X correctly limited the recovery process to three attempts.

Example output:

```text
--- System Status ---
CPU Usage: 0.0353998%
Memory Usage: 8.02646%
Disk Usage: 5.36824%
Process (testprocess): Not Running

[WARNING] Process failure detected
[RECOVERY] Starting recovery for: testprocess
[RECOVERY] Attempt 1/3
[ERROR] Restart command failed
[RECOVERY] Preparing next attempt...
[RECOVERY] Attempt 2/3
[ERROR] Restart command failed
[RECOVERY] Preparing next attempt...
[RECOVERY] Attempt 3/3
[ERROR] Restart command failed
[ERROR] Recovery limit reached
[ERROR] Manual intervention required
[ERROR] Recovery failed
```

This demonstrates that the system does not retry indefinitely.

After the configured recovery limit is reached, it reports:

```text
[ERROR] Manual intervention required
```

This is an important part of the recovery design because a continuously failing recovery operation should eventually stop and require administrator attention.

---

# 4. Recovery Logging

Recovery and failure events are also recorded in:

```text
logs/sentinel.log
```

Example log output:

```text
[2026-10-04 06:21:37] [RECOVERY] Recovery initiated | Starting controlled recovery
[2026-10-04 06:21:41] [ERROR] Recovery failed | Manual intervention required
[2026-10-04 06:21:46] [WARNING] Process failure detected | testprocess is not running
[2026-10-04 06:21:46] [RECOVERY] Recovery initiated | Starting controlled recovery
[2026-10-04 06:21:51] [ERROR] Recovery failed | Manual intervention required
[2026-10-04 06:21:56] [WARNING] Process failure detected | testprocess is not running
[2026-10-04 06:21:56] [RECOVERY] Recovery initiated | Starting controlled recovery
[2026-10-04 06:22:00] [ERROR] Recovery failed | Manual intervention required
[2026-10-04 06:22:05] [WARNING] Process failure detected | testprocess is not running
[2026-10-04 06:22:05] [RECOVERY] Recovery initiated | Starting controlled recovery
[2026-10-04 06:22:08] [ERROR] Recovery failed | Manual intervention required
[2026-10-04 06:22:13] [WARNING] Process failure detected | testprocess is not running
[2026-10-04 06:22:13] [RECOVERY] Recovery initiated | Starting controlled recovery
[2026-10-04 06:22:17] [ERROR] Recovery failed | Manual intervention required
[2026-10-04 06:22:22] [INFO] Sentinel shutting down | Monitoring stopped by signal
```

The log provides a persistent record of important system events.

---

# 5. Graceful Shutdown

Linux-Sentinel-X handles the interrupt signal and shuts down cleanly when:

```text
Ctrl+C
```

is pressed.

Example:

```text
^C
================================
        Linux Sentinel-X
          Shutting down...
================================
```

This demonstrates signal handling and controlled program termination.

---

# Testing Summary

| Test | Expected Result | Status |
|---|---|---|
| System monitoring | CPU, memory and disk information displayed | Passed |
| Process monitoring | Configured process status detected | Passed |
| Process failure detection | Process failure detected | Passed |
| Automatic recovery | Failed process restarted | Passed |
| Recovery verification | Recovered process verified | Passed |
| Recovery attempt limit | Recovery limited to 3 attempts | Passed |
| Manual intervention detection | Reported after recovery failure | Passed |
| Event logging | Failure and recovery events logged | Passed |
| Graceful shutdown | Program terminates cleanly | Passed |
| CMake build | Project builds successfully | Passed |

---

# Development Stages

### Stage 1 — Project Introduction

Defined the purpose and scope of Linux-Sentinel-X.

### Stage 2 — Requirements and Development Plan

Identified the monitoring, process supervision, recovery, configuration, and logging requirements.

### Stage 3 — System Design and Architecture

Designed the project around separate components for monitoring, failure detection, recovery, configuration management, and logging.

### Stage 4 — Implementation

Implemented the project using C++ and Linux system programming concepts.

### Stage 5 — Testing and Validation

Performed controlled process-failure tests and verified monitoring, recovery, retry limits, manual intervention reporting, logging, and graceful shutdown.

---

# Technologies and Concepts Used

### Programming

- C++
- Object-Oriented Programming
- Classes and modular design
- File handling
- Error handling

### Linux

- Linux system programming
- Process management
- Process monitoring
- Signals
- `/proc` filesystem concepts
- Shell commands
- Process control

### Build System

- CMake
- GNU C++ compiler

### Project Management

- Git
- GitHub
- Feature branches
- Pull requests

---

# Project Status

**Stages 1–5 Completed**

- Project introduction completed
- Requirements documented
- System design completed
- Implementation completed
- Testing and validation completed
- System monitoring verified
- Process monitoring verified
- Failure detection verified
- Automatic recovery verified
- Recovery retry limit verified
- Manual intervention reporting verified
- Logging verified
- Graceful shutdown verified
- Final CMake build verified

---

# Conclusion

Linux-Sentinel-X successfully demonstrates a Linux-based monitoring and process supervision workflow implemented in C++.

The system can monitor system resources and a configured Linux process, detect process failures, attempt controlled automatic recovery, verify recovery results, limit repeated recovery attempts, report when manual intervention is required, and record important events through a logging mechanism.

The project demonstrates practical concepts in **Linux system programming, process management, C++, failure detection, recovery management, configuration handling, signal handling, and event logging**.

