# Stage 1 – Project Introduction

## 1. Project Title

**Linux-Sentinel-X**

### Linux System Monitoring, Process Supervision and Recovery System

---

## 2. Project Idea

Linux-Sentinel-X is an individual Linux-based system monitoring and process supervision project.

The system continuously monitors selected Linux system resources and processes. It detects abnormal conditions, identifies process failures, and performs controlled recovery actions when recovery is enabled.

The project combines C++ programming, Linux system programming, process management, configuration handling, logging, and fault-recovery concepts.

---

## 3. Problem Statement

Linux systems run multiple processes and services continuously. A process may stop unexpectedly or system resources may cross defined usage limits.

If these conditions are not detected, they may affect the reliability and normal operation of the system. Manually checking the system continuously is also not practical.

Linux-Sentinel-X aims to provide a simple monitoring and supervision mechanism that can detect selected abnormal conditions, record the events, and attempt controlled recovery when a monitored process fails.

---

## 4. Objective

The main objectives of Linux-Sentinel-X are:

- Monitor important Linux system resources such as CPU, memory, and disk usage.
- Monitor a selected Linux process.
- Detect when the monitored process is no longer running.
- Detect configured resource threshold violations.
- Perform controlled recovery when a monitored process fails.
- Verify whether the recovery was successful.
- Limit the number of automatic recovery attempts.
- Block repeated automatic recovery when the recovery limit is reached.
- Indicate when manual intervention is required.
- Maintain logs of important monitoring, failure, recovery, and shutdown events.
- Demonstrate Linux system programming and C++ object-oriented programming concepts.

---

## 5. Project Scope

The project focuses on:

- Linux system monitoring
- CPU, memory, and disk monitoring
- Process monitoring
- Process failure detection
- Controlled process recovery
- Recovery verification
- Recovery attempt limits
- Manual intervention handling
- Event logging
- Configuration management
- Linux process and system interfaces
- Signal handling
- C++ programming
- CMake-based project building

The project is implemented using C++ on a Linux environment.

---

## 6. Expected Outcome

The expected outcome is a working Linux-based monitoring and supervision system capable of:

1. Collecting selected system resource information.
2. Monitoring a configured Linux process.
3. Detecting configured resource threshold violations.
4. Detecting process failure.
5. Recording important events in log files.
6. Attempting controlled process recovery.
7. Verifying whether the recovery was successful.
8. Limiting repeated recovery attempts when recovery continues to fail.
9. Blocking automatic recovery after the configured recovery limit is reached.
10. Reporting that manual intervention is required when automatic recovery cannot restore the process.
11. Performing a controlled shutdown when the user sends a termination signal.

---

## 7. Application

Linux-Sentinel-X demonstrates concepts that can be useful in:

- Linux system administration
- Linux system monitoring
- Process supervision
- Embedded Linux and system-level software
- Fault detection and recovery
- Reliability-focused software
- Linux system programming

The project can serve as a basic foundation for a larger monitoring or process-supervision system.

---

## 8. Technologies

| **Component** | **Technology** |
|---|---|
| Programming Language | C++ |
| Operating System | Linux |
| Build System | CMake |
| Compiler | GNU C++ |
| Version Control | Git / GitHub |
| Documentation | Markdown |
| System Interfaces | Linux `/proc`, process and system interfaces |
| Logging | File-based event logging |

---

## 9. Stage 1 Outcome

At the end of Stage 1, the project idea, problem statement, objectives, scope, expected outcome, and application area were defined.

The project was planned as a Linux-based monitoring and process supervision system with a focus on failure detection, controlled recovery, logging, and reliability.
