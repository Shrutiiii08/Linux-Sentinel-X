#include "ProcessMonitor.h"

#include <dirent.h>
#include <fstream>
#include <string>

bool ProcessMonitor::isProcessRunning(const std::string& processName) {
    DIR* procDir = opendir("/proc");

    if (procDir == nullptr) {
        return false;
    }

    struct dirent* entry;

    while ((entry = readdir(procDir)) != nullptr) {
        std::string pid = entry->d_name;

        if (pid.empty() ||
            pid.find_first_not_of("0123456789") != std::string::npos) {
            continue;
        }

        std::ifstream commFile("/proc/" + pid + "/comm");

        if (!commFile.is_open()) {
            continue;
        }

        std::string name;
        std::getline(commFile, name);

        if (name == processName) {
            closedir(procDir);
            return true;
        }
    }

    closedir(procDir);
    return false;
}
