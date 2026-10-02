# Linux-Sentinel-X

## Stage 3 – System Design & Architecture

### 1. System Overview

Linux-Sentinel-X is a Linux-based system monitoring and process supervision tool developed using C++.

The system monitors CPU, memory, and disk usage and checks the status of a configured process. It detects abnormal conditions based on configured thresholds, records important events in logs, and can attempt to restart the monitored process when recovery is enabled.

The project also includes a basic Linux character device driver written in C to demonstrate communication between user space and kernel space.

---

### 2. System Architecture

The system consists of two main parts:

**User Space**

The C++ application contains the following modules:

- **SystemInfo** – collects basic Linux system information.
- **ResourceMonitor** – monitors CPU, memory, and disk usage.
- **ProcessMonitor** – checks the configured process.
- **FailureDetector** – detects threshold violations and process failures.
- **RecoveryManager** – attempts to restart the monitored process.
- **Logger** – records important events and actions.
- **ConfigManager** – reads the monitoring configuration.

**Kernel Space**

The Linux character device driver provides a basic device interface for user-space communication.

```text
                 LINUX ENVIRONMENT
┌─────────────────────────────────────────────┐
│                 USER SPACE                  │
│                                             │
│  ┌──────────────┐                           │
│  │ Config File  │                           │
│  └──────┬───────┘                           │
│         ↓                                   │
│  ┌──────────────────────────────────────┐   │
│  │       C++ Linux-Sentinel-X           │   │
│  │                                      │   │
│  │ SystemInfo                           │   │
│  │ ResourceMonitor                      │   │
│  │ ProcessMonitor                       │   │
│  │ FailureDetector                      │   │
│  │ RecoveryManager                      │   │
│  │ Logger                               │   │
│  │ ConfigManager                        │   │
│  └──────────────┬───────────────────────┘   │
│                 │                           │
│          Linux system interfaces            │
│                 │                           │
│                 │       Device File          │
│                 │            │              │
├─────────────────┼────────────┼──────────────┤
│                 │ KERNEL     │ SPACE        │
│                 │            ▼              │
│                 │  ┌────────────────────┐   │
│                 │  │ Character Device   │   │
│                 │  │ Driver             │   │
│                 │  └────────────────────┘   │
└─────────────────────────────────────────────┘
```

---

### 3. Module Responsibilities

| Module | Responsibility |
|---|---|
| SystemInfo | Collect basic Linux system information |
| ResourceMonitor | Monitor CPU, memory, and disk usage |
| ProcessMonitor | Check whether the configured process is running |
| FailureDetector | Compare monitored values with configured limits |
| RecoveryManager | Attempt to restart the configured process |
| Logger | Record events, failures, and recovery actions |
| ConfigManager | Read monitoring settings |
| Device Driver | Provide a basic Linux character-device interface |
| Driver Interface | Handle user-space communication with the device |

---

### 4. Main Data Flow

```text
Configuration
      ↓
Read Settings
      ↓
Collect System / Process Information
      ↓
Check Configured Conditions
      ↓
Failure Detected?
    /       \
   No       Yes
   ↓         ↓
Continue    Log Failure
Monitoring     ↓
          Recovery Enabled?
             /      \
            No      Yes
            ↓        ↓
          Log    Attempt Recovery
                    ↓
                Log Result
                    ↓
             Continue Monitoring
```

---

### 5. Configuration Flow

The configuration file contains:

- Process/service name
- Monitoring interval
- CPU threshold
- Memory threshold
- Disk threshold
- Recovery setting

The configuration flow is:

```text
Configuration File
        ↓
ConfigManager
        ↓
Monitoring Modules
        ↓
FailureDetector
        ↓
RecoveryManager
```

---

### 6. Process Recovery Flow

When the configured process stops:

```text
ProcessMonitor
      ↓
Process Not Running
      ↓
FailureDetector
      ↓
Recovery Enabled?
    /        \
   No        Yes
   ↓          ↓
 Log      RecoveryManager
 Failure       ↓
          Attempt Restart
               ↓
          Check Result
               ↓
           Log Result
```

---

### 7. Character Device Communication

The character driver provides a separate demonstration of user-space and kernel-space communication.

```text
C++ Application
      ↓
Device File
      ↓
Linux Character Driver
      ↓
Kernel Space
```

The driver will implement the basic operations required for a character device:

- Initialization
- Open
- Read
- Write
- Cleanup

---

### 8. Data Structures

The application will use simple structures based on the actual requirements.

**Configuration data:**

```text
Configuration
├── Process name
├── Monitoring interval
├── CPU threshold
├── Memory threshold
├── Disk threshold
└── Recovery enabled
```

**Resource data:**

```text
ResourceData
├── CPU usage
├── Memory usage
└── Disk usage
```

Process-monitoring data will contain the information required to identify and determine the state of the configured process.

---

### 9. Class Design

The C++ application will separate the major responsibilities into classes:

```text
ConfigManager
      ↓
ResourceMonitor ─────┐
                     ↓
ProcessMonitor → FailureDetector
                     ↓
              RecoveryManager
                     ↓
                   Logger
```

`SystemInfo` will provide basic system information. A separate driver interface will handle communication with the character device.

---

### 10. Sequence Diagram

The main failure and recovery sequence is:

```text
ProcessMonitor    FailureDetector    RecoveryManager    Logger
      │                  │                  │              │
      │ Check Process    │                  │              │
      ├─────────────────>│                  │              │
      │                  │                  │              │
      │ Process Failed   │                  │              │
      ├─────────────────>│                  │              │
      │                  │ Detect Failure   │              │
      │                  ├────────────────────────────────>│
      │                  │                  │              │
      │                  │ Recovery Request │              │
      │                  ├─────────────────>│              │
      │                  │                  │              │
      │                  │                  │ Restart      │
      │                  │                  │ Process      │
      │                  │                  │              │
      │                  │ Recovery Result  │              │
      │                  │<─────────────────┤              │
      │                  │                  │              │
      │                  ├────────────────────────────────>│
```

---

### 11. Process State Machine

The monitored process will have the following states:

```text
       ┌───────────┐
       │ STARTING  │
       └─────┬─────┘
             ↓
       ┌───────────┐
       │  RUNNING  │
       └─────┬─────┘
             │
        Process Stops
             ↓
       ┌───────────┐
       │  FAILED   │
       └─────┬─────┘
             │
      Recovery Enabled
             ↓
       ┌───────────┐
       │ RECOVERING│
       └─────┬─────┘
          ┌──┴──┐
       Success Failure
          ↓      ↓
      RUNNING  FAILED
```

---

### 12. Proposed Project Structure

```text
linux-sentinel-x/
│
├── README.md
├── CMakeLists.txt
│
├── docs/
│   ├── stage-1-project-introduction.md
│   ├── stage-2-project-requirements.md
│   └── stage-3-system-design.md
│
├── include/
│   ├── config_manager.h
│   ├── system_info.h
│   ├── resource_monitor.h
│   ├── process_monitor.h
│   ├── failure_detector.h
│   ├── recovery_manager.h
│   └── logger.h
│
├── src/
│   ├── main.cpp
│   ├── config_manager.cpp
│   ├── system_info.cpp
│   ├── resource_monitor.cpp
│   ├── process_monitor.cpp
│   ├── failure_detector.cpp
│   ├── recovery_manager.cpp
│   └── logger.cpp
│
├── driver/
│   └── linux_sentinel_driver.c
│
├── config/
│   └── sentinel.conf
│
└── logs/
```

---

### 13. Implementation Plan

The project will be implemented in the following order:

1. Set up the C++ project and CMake build system.
2. Implement configuration handling.
3. Implement system information collection.
4. Implement CPU, memory, and disk monitoring.
5. Implement process monitoring.
6. Implement failure detection.
7. Implement logging.
8. Implement controlled process recovery.
9. Implement the Linux character device driver.
10. Implement user-space communication with the driver.
11. Integrate all modules.
12. Test the complete system.

---

### 14. Git Strategy

The project will use the `main` branch for the stable project version.

Major milestones will be recorded using meaningful commits, for example:

```text
feat: implement configuration manager
feat: implement system information
feat: implement resource monitoring
feat: implement process monitoring
feat: implement failure detection
feat: implement recovery manager
feat: implement logging
feat: add character device driver
test: verify monitoring and recovery
docs: update project documentation
```

---

### 15. Stage 3 Completion

Stage 3 is complete when the following are defined:

- System architecture
- Module responsibilities
- Main data flow
- Configuration flow
- Recovery flow
- Driver communication
- Required data structures
- Class diagram
- Sequence diagram
- State machine diagram
- Project structure
- Implementation order
- Git strategy


