# Linux-Sentinel-X

## Linux System Monitoring, Process Supervision and Automatic Recovery System

### Project Type

Individual Capstone Project

### Programming Language

C++

### Operating System

Linux

---

## Project Objective

**Linux-Sentinel-X** is a Linux-based system monitoring and process supervision system developed in C++.

The system continuously monitors important system resources and a configured Linux process. When an abnormal condition or process failure is detected, Sentinel-X records the event and can perform controlled automatic recovery.

The recovery mechanism does not blindly restart the process. It:

1. Detects the failure
2. Initiates controlled recovery
3. Verifies whether the process has recovered
4. Retries recovery only within a configured limit
5. Reports manual intervention when recovery cannot be completed

The project demonstrates Linux system programming, C++ object-oriented programming, process monitoring, resource monitoring, failure detection, process recovery, configuration management, signal handling, and event logging.

---

## Core Workflow

```text
Monitor System
      ↓
Detect Abnormal Condition
      ↓
Identify Affected Process
      ↓
Initiate Controlled Recovery
      ↓
Verify Recovery
      ↓
Retry Within Configured Limit
      ↓
Log Result
```

---

## Main Features

- System information monitoring
- CPU usage monitoring
- Memory usage monitoring
- Disk usage monitoring
- Configured process monitoring
- Process failure detection
- Automatic process recovery
- Recovery verification
- Configurable recovery attempt limit
- Retry delay between recovery attempts
- Manual intervention handling
- Configuration file support
- Structured event logging
- Graceful shutdown using Linux signals
- C++ object-oriented design
- CMake-based build system

---

## Recovery Mechanism

The recovery system is one of the core features of Linux-Sentinel-X.

When the monitored process is found to be unavailable, Sentinel-X initiates controlled recovery.

### Successful Recovery

```text
Process Running
      ↓
Process Failure Detected
      ↓
Recovery Initiated
      ↓
Restart Attempt
      ↓
Process Verification
      ↓
Process Running
      ↓
Recovery Successful
```

Example:

```text
[WARNING] Process failure detected
[RECOVERY] Recovery initiated
[RECOVERY] Attempt 1/3
[VERIFY] Checking process...
[INFO] Recovery successful
```

### Failed Recovery

If the process cannot be restarted, Sentinel-X does not retry indefinitely.

```text
Process Failure
      ↓
Recovery Attempt 1
      ↓
Verification Failed
      ↓
Recovery Attempt 2
      ↓
Verification Failed
      ↓
Recovery Attempt 3
      ↓
Verification Failed
      ↓
Recovery Limit Reached
      ↓
Manual Intervention Required
```

Example:

```text
[RECOVERY] Attempt 1/3
[ERROR] Restart command failed

[RECOVERY] Attempt 2/3
[ERROR] Restart command failed

[RECOVERY] Attempt 3/3
[ERROR] Restart command failed

[ERROR] Recovery limit reached
[ERROR] Manual intervention required
```

This prevents the system from continuously attempting recovery without a defined limit.

---

## Project Structure

```text
Linux-Sentinel-X/
│
├── config/
│   └── sentinel.conf
│
├── docs/
│   └── architecture.png
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
│   ├── ProcessMonitor.cpp
│   ├── RecoveryManager.cpp
│   ├── ResourceMonitor.cpp
│   ├── SystemInfo.cpp
│   └── main.cpp
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

## Configuration

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

The configuration allows the monitored process, monitoring interval, resource thresholds, and recovery behavior to be changed without modifying the source code.

---

## Build

From the project directory:

```bash
cmake -S . -B build
```

Then build:

```bash
cmake --build build
```

A successful build produces:

```text
build/linux-sentinel-x
```

---

## Run

Run the application using:

```bash
./build/linux-sentinel-x
```

The program displays system information and continuously monitors the configured process and system resources.

Press:

```text
Ctrl+C
```

to stop Sentinel-X gracefully.

---

## Testing and Validation

Linux-Sentinel-X was tested using controlled process-failure scenarios.

### Test 1 — Successful Automatic Recovery

The configured `testprocess` was intentionally stopped while Sentinel-X was running.

Expected workflow:

```text
Process Running
      ↓
Process Stopped
      ↓
Failure Detected
      ↓
Recovery Initiated
      ↓
Process Restarted
      ↓
Recovery Verified
      ↓
Recovery Successful
```

This test was successfully completed.

---

### Test 2 — Recovery Failure and Manual Intervention

The `testprocess` executable was temporarily made unavailable and the running process was stopped.

Sentinel-X attempted recovery three times.

Expected behavior:

```text
Attempt 1/3 → Failed
Attempt 2/3 → Failed
Attempt 3/3 → Failed
Recovery Limit Reached
Manual Intervention Required
```

This test was successfully completed.

---

### Logging Validation

Recovery events are recorded in:

```text
logs/sentinel.log
```

The log records events such as:

```text
[INFO] Sentinel started
[WARNING] Process failure detected
[RECOVERY] Recovery initiated
[INFO] Recovery successful
```

For failed recovery:

```text
[ERROR] Recovery failed
[ERROR] Manual intervention required
```

---

## Technologies and Concepts

### Programming

- C++
- Object-Oriented Programming
- Classes and modular design
- C++ standard library

### Linux

- Linux process management
- `/proc` system information
- Process monitoring
- Linux signals
- Process control
- Shell/system interaction
- File-based logging

### Build System

- CMake
- GNU C++ compiler

### System Concepts

- CPU monitoring
- Memory monitoring
- Disk monitoring
- Failure detection
- Fault recovery
- Retry mechanisms
- Recovery verification
- Graceful shutdown

---

## Development Stages

1. Project Introduction
2. Project Requirements & Development Plan
3. System Design & Architecture
4. Implementation
5. Testing & Validation

### Current Status

**Stages 1–5 Completed**

- Project introduction completed
- Requirements documented
- System design documented
- Implementation completed
- Testing and validation completed
- Failure detection verified
- Automatic process recovery verified
- Recovery verification verified
- Recovery attempt limit verified
- Manual intervention scenario verified
- Logging verified
- Final build verified

---

## Conclusion

Linux-Sentinel-X demonstrates a complete Linux monitoring and process-supervision workflow rather than simply displaying system statistics.

The system monitors system resources and a configured process, detects failures, initiates controlled recovery, verifies the recovery result, limits repeated recovery attempts, and records the outcome through structured logging.

The project provides a practical demonstration of Linux process management, system monitoring, fault detection, recovery mechanisms, C++ modular design, and Linux system programming concepts.
