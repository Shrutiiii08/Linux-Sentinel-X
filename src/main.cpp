#include <iostream>
#include <thread>
#include <chrono>
#include <csignal>

#include "SystemInfo.h"
#include "ResourceMonitor.h"
#include "ProcessMonitor.h"
#include "FailureDetector.h"
#include "RecoveryManager.h"
#include "Logger.h"
#include "ConfigManager.h"

volatile std::sig_atomic_t running = 1;

void handleSignal(int signal)
{
    if (signal == SIGINT || signal == SIGTERM)
    {
        running = 0;
    }
}

int main()
{
    // Register signal handlers
    std::signal(SIGINT, handleSignal);
    std::signal(SIGTERM, handleSignal);

    Config config;
    ConfigManager configManager;

    // Load configuration
    if (!configManager.loadConfig(
            "config/sentinel.conf", config))
    {
        std::cerr << "[ERROR] Failed to load configuration."
                  << std::endl;

        return 1;
    }

    // Create system components
    SystemInfo systemInfo;
    ResourceMonitor resourceMonitor;
    ProcessMonitor processMonitor;
    FailureDetector failureDetector;

    RecoveryManager recoveryManager(
        config.maxRecoveryAttempts,
        config.retryDelay
    );

    Logger logger;

    // --------------------------------------------------
    // STARTUP
    // --------------------------------------------------

    std::cout << "===================================="
              << std::endl;

    std::cout << "       Linux Sentinel-X"
              << std::endl;

    std::cout << "===================================="
              << std::endl;

    std::cout << "Monitoring: "
              << config.processName
              << std::endl;

    std::cout << "Press Ctrl+C to stop Sentinel-X."
              << std::endl;

    logger.logEvent(
        "INFO",
        "Sentinel started",
        "Monitoring process: " + config.processName
    );

    systemInfo.displaySystemInfo();

    // --------------------------------------------------
    // MONITORING LOOP
    // --------------------------------------------------

    while (running)
    {
        // -------------------------------
        // 1. MONITOR
        // -------------------------------

        double cpuUsage =
            resourceMonitor.getCpuUsage();

        double memoryUsage =
            resourceMonitor.getMemoryUsage();

        double diskUsage =
            resourceMonitor.getDiskUsage();

        bool processRunning =
            processMonitor.isProcessRunning(
                config.processName
            );

        std::cout << "\n--- System Status ---"
                  << std::endl;

        std::cout << "CPU Usage: "
                  << cpuUsage
                  << "%"
                  << std::endl;

        std::cout << "Memory Usage: "
                  << memoryUsage
                  << "%"
                  << std::endl;

        std::cout << "Disk Usage: "
                  << diskUsage
                  << "%"
                  << std::endl;

        std::cout << "Process ("
                  << config.processName
                  << "): "
                  << (processRunning
                          ? "Running"
                          : "Not Running")
                  << std::endl;

        // -------------------------------
        // 2. DETECT
        // -------------------------------

        if (failureDetector.cpuExceeded(
                cpuUsage, config))
        {
            std::cout
                << "[WARNING] CPU threshold exceeded"
                << std::endl;

            logger.logEvent(
                "WARNING",
                "CPU threshold exceeded",
                "CPU usage: " +
                std::to_string(cpuUsage) + "%"
            );
        }

        if (failureDetector.memoryExceeded(
                memoryUsage, config))
        {
            std::cout
                << "[WARNING] Memory threshold exceeded"
                << std::endl;

            logger.logEvent(
                "WARNING",
                "Memory threshold exceeded",
                "Memory usage: " +
                std::to_string(memoryUsage) + "%"
            );
        }

        if (failureDetector.diskExceeded(
                diskUsage, config))
        {
            std::cout
                << "[WARNING] Disk threshold exceeded"
                << std::endl;

            logger.logEvent(
                "WARNING",
                "Disk threshold exceeded",
                "Disk usage: " +
                std::to_string(diskUsage) + "%"
            );
        }

        // -------------------------------
        // 3. PROCESS FAILURE DETECTION
        // -------------------------------

        if (failureDetector.processFailed(
                processRunning))
        {
            std::cout
                << "[WARNING] Process failure detected"
                << std::endl;

            logger.logEvent(
                "WARNING",
                "Process failure detected",
                config.processName +
                " is not running"
            );

            // -------------------------------
            // 4. RECOVER
            // -------------------------------

            if (config.recoveryEnabled)
            {
                logger.logEvent(
                    "RECOVERY",
                    "Recovery initiated",
                    "Starting controlled recovery"
                );

                bool recovered =
                    recoveryManager.recover(
                        config.processName
                    );

                // -------------------------------
                // 5. VERIFY + LOG RESULT
                // -------------------------------

                if (recovered)
                {
                    std::cout
                        << "[INFO] Recovery successful"
                        << std::endl;

                    logger.logEvent(
                        "INFO",
                        "Recovery successful",
                        config.processName +
                        " is running again"
                    );
                }
                else
                {
                    std::cout
                        << "[ERROR] Recovery failed"
                        << std::endl;

                    logger.logEvent(
                        "ERROR",
                        "Recovery failed",
                        "Manual intervention required"
                    );
                }
            }
            else
            {
                logger.logEvent(
                    "WARNING",
                    "Recovery disabled",
                    "Manual intervention required"
                );
            }
        }

        // -------------------------------
        // WAIT FOR NEXT MONITORING CYCLE
        // -------------------------------

        std::this_thread::sleep_for(
            std::chrono::seconds(
                config.monitorInterval
            )
        );
    }

    // --------------------------------------------------
    // CONTROLLED SHUTDOWN
    // --------------------------------------------------

    logger.logEvent(
        "INFO",
        "Sentinel shutting down",
        "Monitoring stopped by signal"
    );

    std::cout << "\n===================================="
              << std::endl;

    std::cout << "       Linux Sentinel-X"
              << std::endl;

    std::cout << "       Shutting down..."
              << std::endl;

    std::cout << "===================================="
              << std::endl;

    return 0;
}
