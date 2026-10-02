#include <iostream>
#include <thread>
#include <chrono>

#include "SystemInfo.h"
#include "ResourceMonitor.h"
#include "ProcessMonitor.h"
#include "FailureDetector.h"
#include "RecoveryManager.h"
#include "Logger.h"
#include "ConfigManager.h"

int main()
{
    Config config;
    ConfigManager configManager;

    if (!configManager.loadConfig("config/sentinel.conf", config))
    {
        std::cerr << "Failed to load configuration." << std::endl;
        return 1;
    }

    SystemInfo systemInfo;
    ResourceMonitor resourceMonitor;
    ProcessMonitor processMonitor;
    FailureDetector failureDetector;
    RecoveryManager recoveryManager;
    Logger logger;

    std::cout << "====================================" << std::endl;
    std::cout << "       Linux Sentinel-X" << std::endl;
    std::cout << "====================================" << std::endl;

    systemInfo.displaySystemInfo();

    while (true)
    {
        double cpuUsage = resourceMonitor.getCpuUsage();
        double memoryUsage = resourceMonitor.getMemoryUsage();
        double diskUsage = resourceMonitor.getDiskUsage();

        bool processRunning =
            processMonitor.isProcessRunning(config.processName);

        std::cout << "\n--- System Status ---" << std::endl;

        std::cout << "CPU Usage: "
                  << cpuUsage << "%" << std::endl;

        std::cout << "Memory Usage: "
                  << memoryUsage << "%" << std::endl;

        std::cout << "Disk Usage: "
                  << diskUsage << "%" << std::endl;

        std::cout << "Process ("
                  << config.processName << "): "
                  << (processRunning ? "Running" : "Not Running")
                  << std::endl;

        if (failureDetector.cpuExceeded(cpuUsage, config))
        {
            logger.logEvent(
                "CPU Threshold",
                "CPU usage above limit",
                "Warning recorded"
            );
        }

        if (failureDetector.memoryExceeded(memoryUsage, config))
        {
            logger.logEvent(
                "Memory Threshold",
                "Memory usage above limit",
                "Warning recorded"
            );
        }

        if (failureDetector.diskExceeded(diskUsage, config))
        {
            logger.logEvent(
                "Disk Threshold",
                "Disk usage above limit",
                "Warning recorded"
            );
        }

        if (failureDetector.processFailed(processRunning))
        {
            logger.logEvent(
                "Process Failure",
                "Process is not running",
                "Recovery attempted"
            );

            if (config.recoveryEnabled)
            {
                recoveryManager.restartProcess(config.processName);
            }
        }

        std::this_thread::sleep_for(
            std::chrono::seconds(config.monitorInterval)
        );
    }

    return 0;
}
