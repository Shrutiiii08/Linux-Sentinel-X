#include <iostream>

#include "FailureDetector.h"
#include "ConfigManager.h"

int main()
{
    FailureDetector detector;
    Config config;

    config.cpuThreshold = 80;
    config.memoryThreshold = 80;
    config.diskThreshold = 80;

    std::cout << "CPU 90%: "
              << detector.cpuExceeded(90, config)
              << std::endl;

    std::cout << "CPU 50%: "
              << detector.cpuExceeded(50, config)
              << std::endl;

    std::cout << "Memory 90%: "
              << detector.memoryExceeded(90, config)
              << std::endl;

    std::cout << "Disk 90%: "
              << detector.diskExceeded(90, config)
              << std::endl;

    std::cout << "Process stopped: "
              << detector.processFailed(false)
              << std::endl;

    std::cout << "Process running: "
              << detector.processFailed(true)
              << std::endl;

    return 0;
}
