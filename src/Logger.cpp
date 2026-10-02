#include "Logger.h"

#include <fstream>
#include <ctime>

bool Logger::logEvent(const std::string& event,
                      const std::string& status,
                      const std::string& action)
{
    std::ofstream logFile("logs/sentinel.log", std::ios::app);

    if (!logFile.is_open())
    {
        return false;
    }

    std::time_t currentTime = std::time(nullptr);

    char* timeString = std::ctime(&currentTime);

    if (timeString != nullptr)
    {
        std::string timestamp(timeString);

        if (!timestamp.empty() && timestamp.back() == '\n')
        {
            timestamp.pop_back();
        }

        logFile << "[" << timestamp << "] "
                << "Event: " << event
                << " | Status: " << status
                << " | Action: " << action
                << '\n';
    }

    logFile.close();

    return true;
}
