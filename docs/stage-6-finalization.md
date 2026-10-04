# Linux-Sentinel-X

## Stage 6 – Finalization

### 1. Overview

Stage 6 is the final stage of the Linux-Sentinel-X project.

The purpose of this stage is to finalize the project after implementation and testing. The finalization process includes completing the project documentation, verifying the project structure, reviewing the implemented functionality, organizing the GitHub repository, and preparing the project for final demonstration and evaluation.

Linux-Sentinel-X is a Linux-based system monitoring and process supervision application developed using C++ and Linux system programming concepts.

The final system provides:

- System information collection
- CPU monitoring
- Memory monitoring
- Disk monitoring
- Process monitoring
- Resource threshold detection
- Process failure detection
- Controlled process recovery
- Recovery attempt limits
- Recovery verification
- Event logging
- Configuration management
- Safe application shutdown
- CMake-based build system
- Git and GitHub version control

---

### 2. Final Project Structure

The final project is organized into separate directories for source code, header files, configuration, documentation and testing.

The main project structure is:

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
│   ├── SystemMonitor.h
│   ├── ProcessMonitor.h
│   ├── FailureDetector.h
│   ├── RecoveryManager.h
│   └── Logger.h
│
├── src/
│   ├── main.cpp
│   ├── ConfigManager.cpp
│   ├── SystemMonitor.cpp
│   ├── ProcessMonitor.cpp
│   ├── FailureDetector.cpp
│   ├── RecoveryManager.cpp
│   └── Logger.cpp
│
├── tests/
│
├── CMakeLists.txt
├── README.md
└── .gitignore
```

The project is organized to keep different responsibilities separated and make the source code easier to understand, maintain and explain.

---

### 3. Final Functional Components

The final implementation consists of the following major components.

#### 3.1 SystemMonitor

The SystemMonitor component collects system resource information.

It provides:

- CPU usage
- Memory usage
- Disk usage

It is used by the main monitoring loop to obtain the current resource status.

#### 3.2 ProcessMonitor

The ProcessMonitor component checks whether the configured Linux process is running.

The process name is obtained from the configuration file.

#### 3.3 FailureDetector

The FailureDetector component checks the monitored values against the configured thresholds.

It detects:

- CPU threshold violations
- Memory threshold violations
- Disk threshold violations
- Process failure

#### 3.4 RecoveryManager

The RecoveryManager controls the recovery process when the monitored process stops.

It:

- Attempts to restart the configured process
- Verifies whether recovery was successful
- Limits repeated recovery attempts
- Prevents unlimited automatic restart attempts
- Reports when manual intervention is required

#### 3.5 Logger

The Logger records important system and recovery events.

Examples include:

- Threshold violations
- Process failure
- Recovery attempts
- Successful recovery
- Failed recovery
- Recovery being blocked
- Manual intervention requirements

#### 3.6 ConfigManager

The ConfigManager reads the monitoring settings from the configuration file.

The configuration includes:

- Process name
- Monitoring interval
- CPU threshold
- Memory threshold
- Disk threshold
- Recovery setting

#### 3.7 Main Application

The `main.cpp` file coordinates the different components and controls the continuous monitoring workflow.

---

### 4. Configuration

The project uses a configuration file:

```text
config/sentinel.conf
```

The configuration allows monitoring parameters to be changed without modifying the source code.

Example configuration:

```text
process_name=testprocess
monitor_interval=5
cpu_threshold=80
memory_threshold=80
disk_threshold=80
recovery_enabled=true
```

This configuration was used during testing to verify process monitoring and recovery functionality.

---

### 5. Build and Execution

Linux-Sentinel-X uses CMake as its build system.

The project can be configured and built using the following commands:

```bash
cmake -S . -B build
cmake --build build
```

The build process successfully produces the Linux-Sentinel-X executable.

The project is designed to run in a Linux environment with the required C++ compiler and build tools.

---

### 6. Final Validation

The project functionality was validated during Stage 5.

The following areas were successfully tested:

| Test Area | Result |
|---|---|
| Project compilation | PASS |
| System information | PASS |
| CPU monitoring | PASS |
| Memory monitoring | PASS |
| Disk monitoring | PASS |
| Process monitoring | PASS |
| Threshold detection | PASS |
| Process failure detection | PASS |
| Process recovery | PASS |
| Recovery verification | PASS |
| Recovery attempt control | PASS |
| Event logging | PASS |
| Configuration handling | PASS |
| Safe shutdown | PASS |
| Module integration | PASS |

The testing confirmed that the major implemented functions operate as intended.

---

### 7. Documentation Finalization

The project documentation was organized into six development stages:

**Stage 1 – Project Introduction**

Describes the project background, problem statement, objectives, scope and expected outcome.

**Stage 2 – Project Requirements & Development Plan**

Defines the functional requirements, non-functional requirements, project modules, scope, acceptance criteria and development plan.

**Stage 3 – System Design & Architecture**

Describes the system architecture, module interaction, monitoring workflow, recovery workflow and design structure.

**Stage 4 – Implementation**

Documents the implemented components, source files, configuration, build system, integration and implementation details.

**Stage 5 – Testing & Validation**

Documents the testing process, test results, failure detection, process recovery, logging and final validation.

**Stage 6 – Finalization**

Documents the final project structure, final validation, repository organization and project completion.

---

### 8. Git and GitHub Repository

The project source code and documentation are maintained using Git and GitHub.

The repository contains:

- Source code
- Header files
- Configuration file
- CMake build configuration
- Documentation
- README
- Test-related files
- Git configuration files

Stage-wise documentation is maintained inside the `docs` directory.

The repository provides a complete record of the project development and final implementation.

---

### 9. Final Project Scope

The final project focuses specifically on Linux user-space system monitoring and process supervision.

### Included

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
- Email or SMS alerting
- Linux kernel-level device driver development

The project intentionally remains a simple, focused and explainable Linux monitoring and process supervision system.

---

### 10. Final Capstone Requirement Check

The final project was reviewed against the main capstone requirements.

| Requirement | Status |
|---|---|
| C/C++ programming | Completed |
| Linux-based implementation | Completed |
| Software/system architecture concepts | Completed |
| Linux system programming concepts | Completed |
| GitHub repository | Completed |
| Source code | Completed |
| README documentation | Completed |
| Stage-wise documentation | Completed |
| Testing and validation | Completed |
| Final demonstration preparation | Completed |

The project uses C++ and Linux system programming concepts throughout the implementation.

---

### 11. Final Project Outcome

Linux-Sentinel-X was successfully developed as a Linux-based system monitoring and process supervision application.

The final application can monitor system resources and a configured process, detect threshold violations and process failures, record important events, and perform controlled process recovery when enabled.

The recovery mechanism includes verification and recovery attempt limits to prevent unlimited automatic restart attempts.

The modular structure separates configuration management, system monitoring, process monitoring, failure detection, recovery and logging responsibilities.

The project was successfully built and tested, and the source code and documentation were organized in the GitHub repository.

---

### 12. Final Conclusion

The Linux-Sentinel-X project has completed the planned development, implementation and testing stages.

The project demonstrates practical application of:

- C++ programming
- Linux system programming
- Process management
- System resource monitoring
- Failure detection
- Controlled process recovery
- Configuration management
- Event logging
- Signal handling
- Modular software design
- CMake build management
- Git and GitHub version control

The final system provides a simple and explainable approach to Linux system monitoring and process supervision.

With the completion of Stage 6, Linux-Sentinel-X is ready for final project submission, GitHub review, project demonstration and evaluation.

---

### 13. Stage 6 Deliverables

The final Stage 6 deliverables include:

- Final project source code
- Final project structure
- Complete stage-wise documentation
- Final README
- Configuration file
- CMake build configuration
- Testing and validation results
- GitHub repository
- Final project presentation/demo preparation

---

### 14. Stage 6 Status

**Stage 6 – Finalization: COMPLETE**

Linux-Sentinel-X has been finalized after completing the required implementation, testing, validation and documentation activities.

The project is ready for final submission and evaluation.
