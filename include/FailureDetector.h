#ifndef FAILURE_DETECTOR_H
#define FAILURE_DETECTOR_H

#include "ConfigManager.h"

class FailureDetector {
public:
    bool cpuExceeded(double cpuUsage, const Config& config);
    bool memoryExceeded(double memoryUsage, const Config& config);
    bool diskExceeded(double diskUsage, const Config& config);
    bool processFailed(bool processRunning);
};

#endif
