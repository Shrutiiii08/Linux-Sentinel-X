#ifndef RECOVERY_MANAGER_H
#define RECOVERY_MANAGER_H

#include <string>

class RecoveryManager {
public:
    bool restartProcess(const std::string& processName);
};

#endif
