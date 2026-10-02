# Linux-Sentinel-X
## Stage 2 – Project Requirements & Development Plan

### 1. Purpose

Linux-Sentinel-X is a Linux system monitoring and process supervision tool.

The application will continuously monitor selected system resources and a configured process. When a defined limit is exceeded or the monitored process stops, the system will detect the problem, record it in a log, and perform a controlled recovery action where applicable.

The project will also include a basic Linux character device driver to demonstrate user-space and kernel-space interaction.

---

### 2. Functional Requirements

The system will provide the following functions:

**FR-01: System Information**

Collect basic information such as:
- Hostname
- Kernel version
- CPU information
- Memory information

**FR-02: Resource Monitoring**

Monitor:
- CPU usage
- Memory usage
- Disk usage

The monitoring interval will be configurable.

**FR-03: Process Monitoring**

Monitor a configured process/service and determine whether it is running.

**FR-04: Failure Detection**

Detect conditions such as:
- CPU usage above the configured threshold
- Memory usage above the configured threshold
- Disk usage above the configured threshold
- Monitored process not running

**FR-05: Logging**

Record important events with:
- Timestamp
- Event
- Current value/status
- Action taken

**FR-06: Recovery**

When the monitored process stops, attempt to restart it if recovery is enabled in the configuration.

**FR-07: Configuration**

Store monitoring settings in a configuration file, including:
- Process/service name
- Monitoring interval
- Resource thresholds
- Recovery setting

**FR-08: Character Device Driver**

Implement a basic Linux character device driver supporting fundamental operations such as device initialization, open, read, write, and cleanup.

**FR-09: Driver Communication**

Demonstrate basic communication between the user-space application and the character device.

---

### 3. Non-Functional Requirements

- The application should run continuously without unnecessary termination.
- Monitoring should have low CPU and memory overhead.
- Code should be divided into modules with clear responsibilities.
- Errors such as invalid configuration, missing processes, and failed file/device operations should be handled.
- The project should maintain a clear Git history and stage-wise documentation.

---

### 4. Project Modules

| Module | Purpose |
|---|---|
| SystemInfo | Collect Linux system information |
| ResourceMonitor | Monitor CPU, memory and disk |
| ProcessMonitor | Check the configured process |
| FailureDetector | Compare values with thresholds |
| RecoveryManager | Restart the monitored process || Logger | Record events and actions |
| ConfigManager | Read project configuration |
| DeviceDriver | Basic Linux character driver |
| DriverInterface | User-space communication with driver |

---

### 5. Project Scope

**Included:**
- Linux system programming
- C++ monitoring application
- CPU, memory and disk monitoring
- Process monitoring
- Threshold detection
- Logging
- Process recovery
- Configuration file
- Linux character device driver
- User-space/driver communication
- Git and GitHub documentation

---

### 6. Development Plan

The project will be developed in the following order:

**Stage 1 – Project Introduction**  
Project idea, problem, objectives and scope.

**Stage 2 – Requirements & Planning**  
Functional requirements, modules, scope and development plan.

**Stage 3 – System Design**  
Architecture, module interaction, data flow, data structures and UML diagrams.

**Stage 4 – Implementation**  
Develop the monitoring application, configuration, logging, process supervision and character driver.

**Stage 5 – Testing & Improvement**  
Test individual modules, integrate them, handle errors and improve reliability.

**Stage 6 – Finalization**  
Complete documentation, testing, results, presentation and GitHub repository.

---

### 7. Stage 2 Deliverables

At the end of Stage 2:

- Project requirements document
- Defined modules and responsibilities
- Defined project scope
- Development plan
- Git commit for Stage 2
- Updated GitHub repository

