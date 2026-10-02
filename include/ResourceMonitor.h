#ifndef RESOURCE_MONITOR_H
#define RESOURCE_MONITOR_H

class ResourceMonitor {
public:
    double getCpuUsage();
    double getMemoryUsage();
    double getDiskUsage();
};

#endif
