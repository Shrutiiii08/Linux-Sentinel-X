#include "RecoveryManager.h"

#include <cstdlib>

bool RecoveryManager::restartProcess(const std::string& processName)
{
    std::string command = "pkill -x " + processName;
    std::system(command.c_str());

    command = processName + " &";
    int result = std::system(command.c_str());

    return result == 0;
}
