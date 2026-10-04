#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <string>

struct Config {
    std::string processName;

    int monitorInterval;

    double cpuThreshold;
    double memoryThreshold;
    double diskThreshold;

    bool recoveryEnabled;

    int maxRecoveryAttempts;
    int retryDelay;
};

class ConfigManager {
public:
    bool loadConfig(
        const std::string& filename,
        Config& config
    );
};

#endif
