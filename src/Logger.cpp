#include "Logger.h"

#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>

std::string Logger::getTimestamp()
{
    std::time_t currentTime = std::time(nullptr);
    std::tm localTime{};

    localtime_r(&currentTime, &localTime);

    std::ostringstream timestamp;

    timestamp << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");

    return timestamp.str();
}

bool Logger::logEvent(const std::string& level,
                      const std::string& event,
                      const std::string& action)
{
    std::ofstream logFile(
        "logs/sentinel.log",
        std::ios::app
    );

    if (!logFile.is_open())
    {
        return false;
    }

    logFile << "["
            << getTimestamp()
            << "] ["
            << level
            << "] "
            << event
            << " | "
            << action
            << '\n';

    logFile.close();

    return true;
}
