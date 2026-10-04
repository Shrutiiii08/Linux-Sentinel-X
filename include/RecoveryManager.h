#ifndef RECOVERY_MANAGER_H
#define RECOVERY_MANAGER_H

#include <string>

class RecoveryManager {
public:
    RecoveryManager(int maxAttempts, int retryDelay);

    bool recover(const std::string& processName);

private:
    bool restartProcess(const std::string& processName);
    bool isProcessRunning(const std::string& processName);
    void waitBeforeRetry();

    int maxAttempts;
    int retryDelay;
};

#endif
