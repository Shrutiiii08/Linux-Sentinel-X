#include "FailureDetector.h"

bool FailureDetector::cpuExceeded(double cpuUsage, const Config& config)
{
    return cpuUsage > config.cpuThreshold;
}

bool FailureDetector::memoryExceeded(double memoryUsage, const Config& config)
{
    return memoryUsage > config.memoryThreshold;
}

bool FailureDetector::diskExceeded(double diskUsage, const Config& config)
{
    return diskUsage > config.diskThreshold;
}

bool FailureDetector::processFailed(bool processRunning)
{
    return !processRunning;
}
