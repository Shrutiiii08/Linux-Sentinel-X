# Linux-Sentinel-X
## Stage 2 – Project Requirements & Development Plan

### 1. Purpose

Linux-Sentinel-X is a Linux system monitoring and process supervision tool developed using C++ and Linux system programming concepts.

The application continuously monitors selected system resources and a configured process. When a defined resource limit is exceeded or the monitored process stops, the system detects the problem, records the event in a log, and performs a controlled recovery action where applicable.

The project focuses on system monitoring, process supervision, failure detection, controlled recovery, configuration management, logging, and safe system operation.

---

### 2. Functional Requirements

The system provides the following functions:

**FR-01: System Information**

The system can collect basic Linux system information such as:
- CPU information
- Memory information
- Kernel/system information

**FR-02: Resource Monitoring**

The system monitors:
- CPU usage
- Memory usage
- Disk usage

The monitoring interval can be configured through the configuration file.

**FR-03: Process Monitoring**

The system monitors a configured Linux process and determines whether the process is running.

**FR-04: Failure Detection**

The system detects conditions such as:
- CPU usage above the configured threshold
- Memory usage above the configured threshold
- Disk usage above the configured threshold
- Monitored process not running

**FR-05: Logging**

The system records important events with:
- Timestamp
- Event description
- Current status
- Action taken

Examples include process failures, recovery attempts, successful recovery, failed recovery, recovery being blocked, and manual intervention requirements.

**FR-06: Recovery**

When the monitored process stops, the system attempts to restart it when automatic recovery is enabled.

**FR-07: Recovery Limit**

The system limits the number of automatic recovery attempts.

If the configured recovery attempts are unsuccessful, further automatic recovery is blocked and the system reports that manual intervention is required.

**FR-08: Recovery Verification**

After a recovery attempt, the system verifies whether the monitored process has successfully started.

**FR-09: Configuration**

Monitoring settings are stored in a configuration file, including:
- Process name
- Monitoring interval
- CPU threshold
- Memory threshold
- Disk threshold
- Recovery setting

**FR-10: Safe Shutdown**

The application handles termination signals and shuts down the monitoring process safely.

---

### 3. Non-Functional Requirements

- The application should be capable of running continuously during monitoring.
- Monitoring should maintain low CPU and memory overhead.
- The code should be divided into modules with clear responsibilities.
- Configuration and runtime errors should be handled appropriately.
- Failed recovery attempts should not result in unlimited restart attempts.
- Important system and recovery events should be recorded in logs.
- The project should maintain clear Git history and stage-wise documentation.
- The application should run in a Linux environment with the required C++ compiler and build tools.

---

### 4. Project Modules

| Module | Purpose |
|---|---|
| `SystemMonitor` | Collect CPU, memory and disk usage |
| `ProcessMonitor` | Check the configured process |
| `FailureDetector` | Detect process failures and threshold violations |
| `RecoveryManager` | Perform and control process recovery |
| `Logger` | Record system and recovery events |
| `ConfigManager` | Read monitoring and recovery configuration |
| `main.cpp` | Coordinate the monitoring workflow |

Each module has a specific responsibility, allowing the project to remain modular, easier to understand, test and maintain.

---

### 5. Project Scope

**Included:**
- Linux system programming
- C++ programming
- CPU monitoring
- Memory monitoring
- Disk monitoring
- Process monitoring
- Threshold detection
- Process failure detection
- Controlled process recovery
- Recovery attempt limits
- Manual intervention handling
- Event logging
- Configuration file
- Signal handling
- CMake build system
- Git and GitHub version control
- Stage-wise project documentation

**Not Included:**
- Graphical user interface
- Cloud-based monitoring
- Remote monitoring
- Database-based monitoring
- Email/SMS alerting
- Kernel-level device driver development

The project intentionally focuses on a simple and explainable Linux monitoring and process supervision system.

---

### 6. Development Plan

The project was developed progressively through the following stages:

**Stage 1 – Project Introduction**  
Defined the project idea, problem statement, objectives, scope, expected outcome and application.

**Stage 2 – Requirements & Planning**  
Defined functional and non-functional requirements, project modules, scope, deliverables and development plan.

**Stage 3 – System Design**  
Designed the system architecture, module responsibilities, monitoring workflow, recovery workflow and UML documentation.

**Stage 4 – Implementation**  
Implemented system monitoring, process monitoring, configuration handling, failure detection, logging, process recovery and safe shutdown.

**Stage 5 – Testing & Improvement**  
Tested normal monitoring, process failure detection, recovery behaviour, recovery failure and manual intervention handling. Identified and fixed implementation issues and improved reliability.

**Stage 6 – Finalization**  
Finalize project documentation, testing results, architecture and UML diagrams, GitHub repository, project report and final demonstration.

---

### 7. Acceptance Criteria

The project is considered successfully implemented when:

- The project builds successfully using CMake.
- CPU, memory and disk usage are monitored.
- The configured process can be monitored.
- Process failure is detected correctly.
- Configured resource thresholds are checked.
- Automatic recovery can be performed when enabled.
- Recovery attempts are limited.
- Recovery success or failure is verified.
- Manual intervention is reported when automatic recovery is blocked.
- Important events are recorded in the log file.
- The application can shut down safely.
- Source code and documentation are available in the GitHub repository.

---

### 8. Stage 2 Deliverables

At the end of Stage 2:

- Project Requirements Document
- Functional requirements
- Non-functional requirements
- Defined project scope
- Defined project modules and responsibilities
- Development plan
- Acceptance criteria
- Stage 2 documentation
- Git commit for Stage 2
- Updated GitHub repository

---

### 9. Stage 2 Outcome

Stage 2 established a clear understanding of what Linux-Sentinel-X should accomplish and how the project would be developed.

The defined requirements and development plan were used as the foundation for the system design, implementation, testing and finalization stages.
