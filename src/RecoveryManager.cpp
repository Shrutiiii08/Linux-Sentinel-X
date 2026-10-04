
#include "RecoveryManager.h"

#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>

RecoveryManager::RecoveryManager(int maxAttempts, int retryDelay)
    : maxAttempts(maxAttempts), retryDelay(retryDelay)
{
}

bool RecoveryManager::recover(const std::string& processName)
{
    std::cout << "[RECOVERY] Starting recovery for: "
              << processName << std::endl;

    for (int attempt = 1; attempt <= maxAttempts; ++attempt)
    {
        std::cout << "[RECOVERY] Attempt "
                  << attempt << "/" << maxAttempts << std::endl;

        if (restartProcess(processName))
        {
            waitBeforeRetry();

            std::cout << "[VERIFY] Checking process..."
                      << std::endl;

            if (isProcessRunning(processName))
            {
                std::cout << "[INFO] Recovery successful"
                          << std::endl;

                return true;
            }

            std::cout << "[VERIFY] Process is still not running"
                      << std::endl;
        }
        else
        {
            std::cout << "[ERROR] Restart command failed"
                      << std::endl;
        }

        if (attempt < maxAttempts)
        {
            std::cout << "[RECOVERY] Preparing next attempt..."
                      << std::endl;

            waitBeforeRetry();
        }
    }

    std::cout << "[ERROR] Recovery limit reached"
              << std::endl;

    std::cout << "[ERROR] Manual intervention required"
              << std::endl;

    return false;
}

bool RecoveryManager::restartProcess(const std::string& processName)
{
    /*
     * First verify that the executable actually exists.
     * 'command -v' searches the PATH.
     *
     * This prevents a missing executable from being
     * incorrectly reported as a successful restart.
     */
    std::string checkCommand =
        "command -v \"" + processName + "\" > /dev/null 2>&1";

    int checkResult = std::system(checkCommand.c_str());

    if (checkResult != 0)
    {
        return false;
    }

    /*
     * The process has already been detected as not running
     * by ProcessMonitor before recovery starts.
     *
     * Therefore, there is no need to call pkill here.
     * Recovery only needs to start the executable.
     */
    std::cout << "[RECOVERY] Starting process..."
              << std::endl;

    std::string startCommand =
        "nohup \"" + processName +
        "\" > /dev/null 2>&1 &";

    int startResult = std::system(startCommand.c_str());

    return startResult == 0;
}

bool RecoveryManager::isProcessRunning(
    const std::string& processName)
{
    std::string checkCommand =
        "pgrep -x \"" + processName +
        "\" > /dev/null 2>&1";

    return std::system(checkCommand.c_str()) == 0;
}

void RecoveryManager::waitBeforeRetry()
{
    std::this_thread::sleep_for(
        std::chrono::seconds(retryDelay)
    );
}

