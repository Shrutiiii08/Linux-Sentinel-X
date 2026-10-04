#include "ConfigManager.h"

#include <fstream>
#include <sstream>

bool ConfigManager::loadConfig(
    const std::string& filename,
    Config& config)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
        {
            continue;
        }

        std::istringstream iss(line);

        std::string key;
        std::string value;

        if (std::getline(iss, key, '=') &&
            std::getline(iss, value))
        {
            if (key == "process_name")
            {
                config.processName = value;
            }
            else if (key == "monitor_interval")
            {
                config.monitorInterval =
                    std::stoi(value);
            }
            else if (key == "cpu_threshold")
            {
                config.cpuThreshold =
                    std::stod(value);
            }
            else if (key == "memory_threshold")
            {
                config.memoryThreshold =
                    std::stod(value);
            }
            else if (key == "disk_threshold")
            {
                config.diskThreshold =
                    std::stod(value);
            }
            else if (key == "recovery_enabled")
            {
                config.recoveryEnabled =
                    (value == "true");
            }
            else if (key == "max_recovery_attempts")
            {
                config.maxRecoveryAttempts =
                    std::stoi(value);
            }
            else if (key == "retry_delay")
            {
                config.retryDelay =
                    std::stoi(value);
            }
        }
    }

    file.close();

    return true;
}
