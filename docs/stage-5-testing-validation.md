# Linux-Sentinel-X

# Stage 5 – Testing & Integration

## 1. Stage Objective

The objective of Stage 5 was to test and validate the implemented Linux-Sentinel-X system.

Testing was performed to verify that the individual modules work correctly and that they operate together as an integrated Linux monitoring and process supervision system.

The testing focused on:

- System information collection
- CPU monitoring
- Memory monitoring
- Disk monitoring
- Process monitoring
- Threshold detection
- Process failure detection
- Controlled process recovery
- Recovery verification
- Recovery attempt control
- Event logging
- Configuration handling
- Safe shutdown
- Complete project build and integration

---

## 2. Build Verification

The project was successfully configured and built using CMake.

The project was built using:

```bash
cmake --build build
```

The build completed successfully and produced the Linux-Sentinel-X executable.

The successful build confirmed that the implemented source files and modules could be compiled and linked together correctly.

**Result: PASS**

---

## 3. System Information Test

Linux-Sentinel-X successfully collected and displayed basic Linux system information.

The information included:

- Hostname
- Linux kernel version
- CPU information
- Memory information

Example system information obtained during testing:

```text
Hostname: LAPTOP-EE53Q5M4
Kernel: 6.18.33.1-microsoft-standard-WSL2
CPU: 13th Gen Intel(R) Core(TM) i7-13620H
```

This confirmed that the system information component was working correctly in the Linux environment.

**Result: PASS**

---

## 4. Resource Monitoring Test

The application was tested for continuous monitoring of system resources.

The monitored resources were:

- CPU usage
- Memory usage
- Disk usage

Example monitoring output:

```text
CPU Usage: 0.0313868%
Memory Usage: 7.7303%
Disk Usage: 5.36056%
```

The application successfully collected and displayed resource usage during the monitoring cycle.

**Result: PASS**

---

## 5. Process Monitoring Test

The configured Linux process was monitored during application execution.

The ProcessMonitor component successfully determined whether the configured process was running.

Example:

```text
Process (bash): Running
```

The process status was checked during each monitoring cycle.

**Result: PASS**

---

## 6. Failure Detection Test

Failure detection was tested by monitoring the configured process and checking the configured resource thresholds.

The system was able to detect:

- A monitored process that was no longer running.
- CPU usage above the configured threshold.
- Memory usage above the configured threshold.
- Disk usage above the configured threshold.

When a failure condition was detected, the corresponding event was passed to the logging and recovery workflow.

Example event:

```text
Event: CPU Threshold
Status: CPU usage above limit
Action: Warning recorded
```

**Result: PASS**

---

## 7. Process Recovery Test

The process recovery mechanism was tested by creating a process failure condition.

When the monitored process was detected as not running, the RecoveryManager checked whether automatic recovery was enabled.

The recovery workflow was:

```text
Process Running
      |
      v
Process Stops
      |
      v
Failure Detected
      |
      v
Recovery Attempt
      |
      v
Process Restart
      |
      v
Recovery Verification
      |
      v
Process Running
```

The monitoring system successfully detected the process failure and attempted to restart the configured process.

After the recovery attempt, the process status was checked again.

**Result: PASS**

---

## 8. Recovery Verification Test

The recovery mechanism was tested to ensure that the application did not assume that a recovery attempt was successful.

After attempting to restart the monitored process, Linux-Sentinel-X checked the process status again.

The recovery result was then recorded according to the actual process state.

This verified the complete recovery workflow:

```text
Failure Detection
       ↓
Recovery Attempt
       ↓
Process Status Check
       ↓
Success / Failure
       ↓
Log Result
```

**Result: PASS**

---

## 9. Recovery Attempt Limit Test

The RecoveryManager was also tested to ensure that the application does not perform unlimited recovery attempts.

When repeated recovery attempts are unsuccessful, the configured recovery limit is reached.

After the limit is reached:

- Further automatic recovery is blocked.
- The event is recorded in the log.
- Manual intervention is reported as required.

This provides controlled recovery behaviour and prevents continuous restart attempts.

**Result: PASS**

---

## 10. Logging Test

The logging mechanism was tested during monitoring and failure scenarios.

The log records important events such as:

- Threshold violations
- Process failures
- Recovery attempts
- Successful recovery
- Failed recovery
- Recovery being blocked
- Manual intervention requirements

The log file was checked to verify that important events were being recorded.

Example:

```text
Event: Process Failure
Status: Process is not running
Action: Recovery attempted
```

This confirmed that the monitoring and recovery events were being recorded correctly.

**Result: PASS**

---

## 11. Configuration Test

The application was tested using the project configuration file:

```text
config/sentinel.conf
```

The configuration contains parameters such as:

```text
process_name=bash
monitor_interval=5
cpu_threshold=80
memory_threshold=80
disk_threshold=80
recovery_enabled=true
```

The application successfully loaded and used these values during execution.

This confirmed that monitoring behaviour could be controlled through the configuration file without changing the source code.

**Result: PASS**

---

## 12. Safe Shutdown Test

The application was tested for controlled termination.

Linux-Sentinel-X handles termination signals and stops the monitoring loop safely.

The application exits in a controlled manner instead of depending only on forced termination.

**Result: PASS**

---

## 13. Integration Test

After individual functionality was verified, the complete application was tested as an integrated system.

The integrated workflow was:

```text
ConfigManager
      |
      v
SystemInfo / ResourceMonitor
      |
      v
ProcessMonitor
      |
      v
FailureDetector
      |
      v
Logger
      |
      v
RecoveryManager
      |
      v
Recovery Verification
      |
      v
Continue Monitoring
```

The integration test confirmed that the major components could work together during a complete monitoring cycle.

**Result: PASS**

---

## 14. Issues Identified and Improvements

During implementation and testing, several areas were refined to improve the reliability and maintainability of the project.

The improvements included:

- Controlled process recovery.
- Recovery attempt limits.
- Recovery result verification.
- Improved failure event logging.
- Safe handling of termination signals.
- Configuration-based monitoring settings.
- Separation of functionality into independent modules.
- Improved handling of recovery failure conditions.

These improvements helped make the monitoring and recovery workflow more controlled and predictable.

---

## 15. Final Validation Results

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

---

## 16. Stage 5 Conclusion

Linux-Sentinel-X was successfully tested after the implementation of its major monitoring and process supervision components.

The testing demonstrated that the system can:

1. Collect Linux system information.
2. Monitor CPU, memory and disk usage.
3. Monitor a configured Linux process.
4. Detect configured threshold violations.
5. Detect process failure.
6. Attempt controlled process recovery.
7. Verify the result of a recovery attempt.
8. Limit repeated recovery attempts.
9. Record important monitoring and recovery events.
10. Load monitoring settings from the configuration file.
11. Shut down safely.
12. Operate as an integrated Linux monitoring application.

The successful Stage 5 testing provided the validation required before moving to **Stage 6 – Final Implementation & Presentation**.
