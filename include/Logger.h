#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
public:
    bool logEvent(const std::string& level,
                  const std::string& event,
                  const std::string& action);

private:
    std::string getTimestamp();
};

#endif
