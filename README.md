# Linux-Sentinel-X

## Linux System Monitoring, Process Supervision and Recovery System

### Project Type

Individual Capstone Project

### Programming Language

C++

### Operating System

Linux

### Project Objective

Linux-Sentinel-X is a Linux-based system monitoring and process supervision system developed in C++. 
The project monitors important system resources and a configured process, detects abnormal conditions, records failure events, 
and performs controlled recovery actions.

The project demonstrates Linux system programming concepts, C++ object-oriented programming, process monitoring, resource monitoring, failure detection,
 recovery management, configuration handling, and logging.

### Main Components

- System Information Monitoring
- CPU Usage Monitoring
- Memory Usage Monitoring
- Disk Usage Monitoring
- Process Monitoring
- Process Supervision
- Failure Detection
- Automatic Process Recovery
- Configuration Management
- Event Logging
- C++ Object-Oriented Programming
- Linux System Programming

### Project Structure

```text
Linux-Sentinel-X/
├── config/
├── docs/
├── include/
├── src/
├── tests/
├── logs/
├── CMakeLists.txt
└── README.md
```

### Development Stages

1. Project Introduction
2. Project Requirements & Development Plan
3. System Design & Architecture
4. Implementation
5. Testing & Validation

### Testing and Validation

The project was tested through a final functional workflow.

The configured test process was intentionally stopped to simulate a process failure. 
Linux-Sentinel-X successfully detected the failure and attempted automatic recovery.

The recovery workflow was successfully verified as:

```text
Process Running
       ↓
Process Stopped
       ↓
Failure Detected
       ↓
Recovery Attempted
       ↓
Process Running Again
```

The project was also successfully compiled using CMake and the monitoring output was verified for CPU usage, memory usage, disk usage, 
and process status.

### Configuration

The monitoring configuration is stored in:

```text
config/sentinel.conf
```

Example configuration:

```text
process_name=testprocess
monitor_interval=5
cpu_threshold=80
memory_threshold=80
disk_threshold=80
recovery_enabled=true
```

### Build

To build the project:

```bash
cmake --build build
```

### Run

To run Linux-Sentinel-X:

```bash
./build/linux-sentinel-x
```

### Project Status

**Stages 1–5 Completed**

- Project introduction completed
- Requirements documented
- System design documented
- Implementation completed
- Testing and validation completed
- Failure detection verified
- Automatic process recovery verified
- Logging verified
- Final build verified

### Conclusion

Linux-Sentinel-X successfully demonstrates a Linux-based monitoring and process supervision workflow. 
The system can monitor system resources and a configured process, detect process failure, attempt automatic recovery, and 
record failure and recovery events through the logging mechanism.
