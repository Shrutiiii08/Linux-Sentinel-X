# Stage 4 – Implementationx

## 1. Objective

The objective of Stage 4 was to implement the main functional components of Linux Sentinel-X.

The system was developed as a Linux-based system monitoring and recovery application using C++.

The implementation focuses on:

- System information
- CPU monitoring
- Memory monitoring
- Disk monitoring
- Process monitoring
- Failure detection
- Automatic recovery
- Event logging
- Configuration management

---

## 2. Implemented Components

### 2.1 SystemInfo

File:

    include/SystemInfo.h
    src/SystemInfo.cpp

Purpose:

The SystemInfo component collects and displays basic Linux system information.

It displays:

- Hostname
- Kernel version
- CPU information
- Memory information

---

### 2.2 ResourceMonitor

File:

    include/ResourceMonitor.h
    src/ResourceMonitor.cpp

Purpose:

The ResourceMonitor component monitors system resource usage.

It provides:

- CPU usage
- Memory usage
- Disk usage

The collected values are displayed continuously by the main monitoring program.

---

### 2.3 ProcessMonitor

File:

    include/ProcessMonitor.h
    src/ProcessMonitor.cpp

Purpose:

The ProcessMonitor component checks whether a configured Linux process is currently running.

The process name is obtained from the configuration file.

---

### 2.4 ConfigManager

File:

    include/ConfigManager.h
    src/ConfigManager.cpp

Purpose:

The ConfigManager reads monitoring settings from the configuration file.

Configuration file:

    config/sentinel.conf

The configuration contains:

- Process name
- Monitoring interval
- CPU threshold
- Memory threshold
- Disk threshold
- Recovery setting

---

### 2.5 FailureDetector

File:

    include/FailureDetector.h
    src/FailureDetector.cpp

Purpose:

The FailureDetector checks whether monitored values have exceeded their configured thresholds.

It checks:

- CPU threshold
- Memory threshold
- Disk threshold
- Process failure

When a failure condition is detected, the appropriate event is passed to the logging and recovery components.

---

### 2.6 RecoveryManager

File:

    include/RecoveryManager.h
    src/RecoveryManager.cpp

Purpose:

The RecoveryManager attempts to restart the configured process when a process failure is detected and recovery is enabled.

The recovery mechanism was tested using a temporary test process.

The test confirmed that when the monitored process was stopped, Linux Sentinel-X detected the failure and attempted to restart the process.

---

### 2.7 Logger

File:

    include/Logger.h
    src/Logger.cpp

Purpose:

The Logger records important monitoring events.

Log file:

    logs/sentinel.log

Examples of recorded events include:

- CPU threshold exceeded
- Memory threshold exceeded
- Disk threshold exceeded
- Process failure
- Recovery attempt

---

## 3. Main Program Integration

File:

    src/main.cpp

The main program integrates all implemented components.

The monitoring flow is:

    Load Configuration
            |
            v
    Display System Information
            |
            v
    Monitor CPU, Memory and Disk
            |
            v
    Check Monitored Process
            |
            v
    Detect Failure Conditions
            |
            v
    Log Events
            |
            v
    Attempt Recovery
            |
            v
    Repeat After Monitoring Interval

The monitoring loop runs continuously according to the configured monitoring interval.

---

## 4. Build System

File:

    CMakeLists.txt

CMake is used to build the Linux Sentinel-X application.

The project uses:

- C++17
- CMake
- GNU C++ compiler

The project was successfully configured and built using:

    cmake --build build

The final executable is:

    build/linux-sentinel-x

---

## 5. Functional Verification

The implementation was tested successfully.

### Normal Monitoring

Linux Sentinel-X successfully displayed:

- Hostname
- Kernel information
- CPU information
- Memory information
- CPU usage
- Memory usage
- Disk usage
- Process status

### Failure Detection

A temporary test process named `testprocess` was used to verify process monitoring.

The process was detected as running.

After the process was intentionally stopped, Linux Sentinel-X detected:

    Process (testprocess): Not Running

### Automatic Recovery

After detecting the process failure, the RecoveryManager attempted to restart the process.

The next monitoring cycle showed:

    Process (testprocess): Running

This confirmed that the process recovery mechanism was functioning.

### Logging

The logging system was also verified.

The log contained events such as:

    CPU Threshold
    Process Failure
    Recovery attempted

---

## 6. Git Version Control

The completed Stage 4 implementation was committed to Git.

Commit:

    9a93eb2

Commit message:

    Add failure detection and recovery

The changes were successfully pushed to the GitHub repository.

---

## 7. Stage 4 Status

Stage 4 implementation is complete.

Completed components:

- System information
- Resource monitoring
- Process monitoring
- Configuration management
- Failure detection
- Recovery management
- Event logging
- Main program integration
- CMake build
- Functional verification
- GitHub version control

Stage 4 provides the working implementation required for the next stage: testing, integration and improvement.
