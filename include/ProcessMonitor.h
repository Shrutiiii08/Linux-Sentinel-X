#ifndef PROCESS_MONITOR_H
#define PROCESS_MONITOR_H

#include <string>

class ProcessMonitor {
public:
    bool isProcessRunning(const std::string& processName);
};

#endif
