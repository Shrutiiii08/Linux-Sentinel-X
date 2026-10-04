# Stage 1 – Project Introduction

## 1. Project Title

**Linux-Sentinel-X**

### Linux System Monitoring, Process Supervision and Recovery System

---

## 2. Project Idea

Linux-Sentinel-X is an individual Linux-based system monitoring and process supervision project developed using C++ and Linux system programming concepts.

The system continuously monitors selected system resources and a configured Linux process. It detects abnormal conditions such as process failure and configured resource threshold violations, records important events, and performs controlled recovery actions when automatic recovery is enabled.

The project is designed to demonstrate practical Linux system programming, process management, monitoring, failure detection, recovery, configuration handling, logging, and signal handling.

---

## 3. Problem Statement

Linux systems run multiple processes and services continuously. A process may terminate unexpectedly or system resources may reach configured usage limits.

Manually checking these conditions continuously is difficult and inefficient. A simple monitoring and supervision mechanism is therefore useful for detecting failures and providing an appropriate response.

Linux-Sentinel-X addresses this problem by continuously monitoring selected system conditions, detecting failures, recording events, and attempting controlled recovery when configured.

If automatic recovery cannot successfully restore the monitored process after the configured number of attempts, the system blocks further automatic recovery and reports that manual intervention is required.

---

## 4. Objectives

The main objectives of Linux-Sentinel-X are:

- Monitor CPU, memory, and disk usage.
- Monitor a selected Linux process.
- Detect when the monitored process is no longer running.
- Detect configured resource threshold violations.
- Perform controlled automatic recovery when applicable.
- Limit the number of automatic recovery attempts.
- Detect unsuccessful recovery and require manual intervention.
- Maintain timestamped logs of important events.
- Read monitoring and recovery settings from a configuration file.
- Demonstrate Linux process management and system programming.
- Demonstrate C++ object-oriented programming in a Linux environment.
- Provide a simple and understandable system-monitoring architecture.

---

## 5. Project Scope

The project focuses on the following areas:

- Linux system monitoring
- CPU, memory, and disk monitoring
- Process monitoring
- Process failure detection
- Process recovery
- Recovery attempt limits
- Manual intervention handling
- Event logging
- Configuration management
- Linux system interfaces such as `/proc`
- Linux process and signal management
- C++ programming
- CMake-based project building
- Git-based version control

The project is implemented using C++ and Linux system programming facilities and is intended to run in a Linux environment.

---

## 6. Expected Outcome

The expected outcome is a working Linux-based monitoring and process supervision system that can:

1. Collect selected system resource information.
2. Monitor a configured Linux process.
3. Detect process failures and configured threshold violations.
4. Record monitoring and recovery events with timestamps.
5. Attempt controlled recovery when enabled.
6. Limit repeated recovery attempts.
7. Report when automatic recovery fails and manual intervention is required.
8. Stop monitoring safely when the program receives a termination signal.

---

## 7. Application

The concepts demonstrated by Linux-Sentinel-X can be useful in:

- Linux system administration
- Process supervision
- System monitoring
- Embedded Linux applications
- Reliability and fault-recovery systems
- System-level software development
- Basic infrastructure monitoring

The project serves as a practical demonstration of how a Linux application can monitor system conditions, detect failures, and respond to them in a controlled manner.

---

## 8. Technologies and Tools

| Component | Technology |
|---|---|
| Programming Language | C++ |
| Operating System | Linux |
| System Interfaces | Linux `/proc`, process and signal interfaces |
| Build System | CMake |
| Compiler | GNU C++ |
| Version Control | Git / GitHub |
| Documentation | Markdown |
| Configuration | Configuration file |
| Logging | Timestamped application logs |

---

## 9. Stage 1 Outcome

At the end of Stage 1, the project idea, problem statement, objectives, scope, expected outcome, applications, and technology requirements were defined.

The project was then taken forward to the requirements, system design, implementation, and testing stages.
