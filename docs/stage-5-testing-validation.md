# Stage 5 - Testing and Validation

## 1. Overview

Linux-Sentinel-X was tested after implementation to verify system monitoring, process monitoring, failure detection, process recovery, 
logging, and successful project compilation.

## 2. Build Verification

The project was built successfully using the command `cmake --build build`. The build completed successfully and produced the Linux-Sentinel-X executable.

## 3. System Monitoring Test

Linux-Sentinel-X successfully displayed important system information including the hostname, Linux kernel version, CPU information, and memory information. 
The application also successfully monitored CPU usage, memory usage, and disk usage.

Example system information displayed by the application:

Hostname: LAPTOP-EE53Q5M4
Kernel: 6.18.33.1-microsoft-standard-WSL2
CPU: 13th Gen Intel(R) Core(TM) i7-13620H

## 4. Process Monitoring Test

The configured process for testing was testprocess. 
When the process was running, Linux-Sentinel-X correctly detected and displayed the status as "Process (testprocess): Running".

## 5. Failure Detection Test

The testprocess was intentionally stopped using the command `pkill -x testprocess`. 
Linux-Sentinel-X successfully detected that the process had stopped and displayed "Process (testprocess): Not Running".

## 6. Process Recovery Test

After detecting that testprocess was not running, Linux-Sentinel-X attempted to restart the process using the RecoveryManager component.
 The recovery test successfully demonstrated the following sequence:

Running -> Not Running -> Running

This confirmed that Linux-Sentinel-X can detect a process failure and automatically attempt to recover the failed process.

## 7. Logging Test

The Sentinel-X log file was checked using the command `tail -n 20 logs/sentinel.log`. The log contained process failure events and recovery attempts.

Example log entry:

Event: Process Failure | Status: Process is not running | Action: Recovery attempted

This confirmed that process failure and recovery attempts are being recorded in the log file.

## 8. Configuration Test

The monitoring configuration was verified with the following settings:

process_name=testprocess
monitor_interval=5
cpu_threshold=80
memory_threshold=80
disk_threshold=80
recovery_enabled=true

These settings were successfully used during the final testing process.

## 9. Final Validation Result

Project compilation: PASS
System information monitoring: PASS
CPU monitoring: PASS
Memory monitoring: PASS
Disk monitoring: PASS
Process detection: PASS
Process failure detection: PASS
Automatic process recovery: PASS
Failure logging: PASS
Recovery attempt logging: PASS

## 10. Conclusion

Linux-Sentinel-X was successfully built and tested. 
The final functional test demonstrated that the system can monitor system resources, monitor a configured process, 
detect when the process stops, attempt automatic recovery, and detect the process after it has been restarted. 
The logging mechanism also recorded process failure and recovery attempts. 
Therefore, the implemented monitoring, failure detection, recovery, and logging functionality was successfully validated during Stage 5.
