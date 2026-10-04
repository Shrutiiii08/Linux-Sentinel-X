# Linux-Sentinel-X

## Linux System Monitoring, Process Supervision and Recovery

Linux Sentinel-X is an individual Linux-based monitoring project developed using C++. The main purpose of the project is to monitor important system resources and a selected Linux process continuously.

The system checks CPU usage, memory usage, disk usage and the status of a configured process. If the monitored process stops running, Sentinel-X detects the failure and tries to recover the process automatically.

If the recovery attempts fail after the configured limit, automatic recovery is blocked and the system reports that **manual intervention is required**. This prevents the program from continuously trying to restart a failed process.

The project demonstrates practical concepts of Linux, C++, system monitoring, process management, recovery handling, configuration files, logging and CMake.

---

## Project Type

**Individual Capstone Project**

---

## Programming Language

**C++**

---

## Operating System

**Linux**

The project was developed and tested in a Linux environment using Ubuntu/WSL.

---

## Build System

**CMake**

---

## Compiler

**GNU C++ Compiler (g++)**

---

## Main Features

### 1. System Monitoring

Linux Sentinel-X continuously monitors:

- CPU usage
- Memory usage
- Disk usage
- Configured process status

The current system status is displayed in the terminal during every monitoring cycle.

---

### 2. Process Monitoring

The project monitors a process specified in the configuration file.

For example:

```text
Process (testprocess): Running
```

If the process is stopped:

```text
Process (testprocess): Not Running
```

Sentinel-X detects this as a process failure.

---

### 3. Failure Detection

The system checks whether configured resource limits are exceeded.

It can detect:

- High CPU usage
- High memory usage
- High disk usage
- Process failure

Warnings are displayed in the terminal and recorded in the log file.

---

### 4. Automatic Recovery

When the monitored process is not running, Sentinel-X starts the recovery process.

The recovery system uses a limited number of attempts.

Example:

```text
[RECOVERY] Starting recovery for: testprocess
[RECOVERY] Attempt 1/3
[RECOVERY] Starting process...
[VERIFY] Checking process...
[INFO] Recovery successful
```

After starting the process, Sentinel-X checks whether the process is actually running before considering the recovery successful.

---

### 5. Recovery Failure Handling

If the recovery command fails, Sentinel-X does not keep trying forever.

For example:

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

After the maximum number of attempts is reached, automatic recovery is blocked.

---

### 6. Manual Intervention

Manual intervention is used as a safety mechanism when automatic recovery cannot restore the monitored process.

After recovery fails, the system displays:

```text
[ERROR] Recovery failed
[ERROR] Automatic recovery blocked. Manual intervention required.
```

On the next monitoring cycles, Sentinel-X does not repeatedly attempt recovery.

Instead, it reports:

```text
[WARNING] Process failure detected
[WARNING] Automatic recovery is blocked. Manual intervention required.
```

This prevents an endless recovery loop.

Once the monitored process is running again, the recovery block is cleared and automatic recovery becomes available again.

---

### 7. Configuration File

The monitoring settings are stored in:

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
max_recovery_attempts=3
retry_delay=2
recovery_enabled=true
```

The configuration file makes it easier to change monitoring settings without modifying the source code.

---

### 8. Logging

Important events are stored in:

```text
logs/sentinel.log
```

The log records events such as:

- Sentinel startup
- Resource warnings
- Process failure
- Recovery attempts
- Recovery success
- Recovery failure
- Recovery being blocked
- Manual intervention requirement
- Sentinel shutdown

Example:

```text
[2026-10-04 07:34:42] [WARNING] Process failure detected | testprocess is not running
[2026-10-04 07:34:42] [WARNING] Recovery blocked | Manual intervention required
```

---

### 9. Controlled Shutdown

The program can be stopped safely using:

```text
Ctrl+C
```

The program handles the shutdown signal and records the shutdown event in the log.

Example:

```text
[INFO] Sentinel shutting down | Monitoring stopped by signal
```

---

## Project Structure

```text
Linux-Sentinel-X/
│
├── config/
│   └── sentinel.conf
│
├── docs/
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
├── CMakeLists.txt
├── README.md
└── .gitignore
```

---

## Main Components

### SystemInfo

Collects and displays basic information about the Linux system.

### ResourceMonitor

Monitors:

- CPU usage
- Memory usage
- Disk usage

### ProcessMonitor

Checks whether the configured process is currently running.

### FailureDetector

Checks system resource values and process status to identify failures or threshold violations.

### RecoveryManager

Handles the recovery process when the monitored process stops running.

It also controls:

- Maximum recovery attempts
- Retry delay
- Recovery verification
- Recovery failure handling

### ConfigManager

Reads monitoring settings from the configuration file.

### Logger

Stores important system and recovery events in the log file.

### main.cpp

Controls the overall workflow:

```text
Monitor
   ↓
Detect
   ↓
Recover
   ↓
Verify
   ↓
Log Result
   ↓
Continue Monitoring
```

---

## How the Project Works

The basic working flow of Linux Sentinel-X is:

```text
Start Sentinel-X
        ↓
Load Configuration
        ↓
Display System Information
        ↓
Monitor CPU / Memory / Disk
        ↓
Check Process Status
        ↓
Is there a failure?
     /       \
   No         Yes
   ↓           ↓
Continue    Start Recovery
Monitoring      ↓
             Attempt Recovery
                  ↓
             Verify Process
              /        \
           Success      Failure
             ↓            ↓
       Continue       Retry until
       Monitoring     limit reached
                          ↓
                 Block Automatic Recovery
                          ↓
                 Manual Intervention Required
```

---

## Example: Successful Recovery

If the monitored process is stopped and can be restarted successfully:

```text
Process (testprocess): Not Running

[WARNING] Process failure detected
[RECOVERY] Starting recovery for: testprocess
[RECOVERY] Attempt 1/3
[RECOVERY] Starting process...
[VERIFY] Checking process...
[INFO] Recovery successful
```

The next monitoring cycle shows:

```text
Process (testprocess): Running
```

---

## Example: Failed Recovery

If the process cannot be started:

```text
[WARNING] Process failure detected
[RECOVERY] Starting recovery for: testprocess

[RECOVERY] Attempt 1/3
[ERROR] Restart command failed

[RECOVERY] Attempt 2/3
[ERROR] Restart command failed

[RECOVERY] Attempt 3/3
[ERROR] Restart command failed

[ERROR] Recovery limit reached
[ERROR] Manual intervention required
```

The recovery system then becomes blocked:

```text
[WARNING] Automatic recovery is blocked. Manual intervention required.
```

This state continues until the monitored process is running again.

---

## Building the Project

From the project directory:

```bash
cmake -S . -B build
```

Then build the project:

```bash
cmake --build build
```

If the build is successful, the executable is created in the build directory.

---

## Running the Project

Run:

```bash
./build/linux-sentinel-x
```

The program will start monitoring according to the configuration in:

```text
config/sentinel.conf
```

---

## Testing Manual Intervention

To test the manual intervention mechanism, configure a process that can be stopped and controlled during testing.

Check whether the process is running:

```bash
pgrep -x testprocess
```

Stop the process:

```bash
pkill -x testprocess
```

Then observe the Sentinel-X terminal output.

If automatic recovery cannot restart the process, the system should eventually display:

```text
[ERROR] Recovery limit reached
[ERROR] Manual intervention required
[ERROR] Recovery failed
[ERROR] Automatic recovery blocked. Manual intervention required.
```

The log can be checked using:

```bash
tail -30 logs/sentinel.log
```

---

## Technologies and Concepts Used

- C++
- Linux
- Linux process management
- Linux system monitoring
- CPU monitoring
- Memory monitoring
- Disk monitoring
- Process detection
- Automatic recovery
- Manual intervention handling
- Configuration management
- File handling
- Logging
- Signal handling
- CMake
- Git and GitHub

---

## What I Learned

Through this project, I worked with practical Linux and C++ concepts such as process management, system resource monitoring, Linux commands, signal handling, configuration files and logging.

I also learned how to design a recovery mechanism with a limited number of attempts and how to handle recovery failure safely using a manual intervention state.

The project helped me understand how a monitoring program can continuously observe a system, detect failures and take controlled actions when required.

---

## Future Improvements

Some possible improvements for the project are:

- Add CPU temperature monitoring
- Add network status monitoring
- Add more detailed process information
- Improve log formatting
- Add a simple monitoring dashboard
- Add support for monitoring multiple processes

---

## Author

**Shruti Shriya**

B.Tech Computer Science and Engineering

ITER, Siksha 'O' Anusandhan

---

## Project Repository

GitHub:

**Linux-Sentinel-X**

The project is developed as an individual Linux and C++ capstone project.
