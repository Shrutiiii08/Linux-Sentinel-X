#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
public:
    bool logEvent(const std::string& event,
                  const std::string& status,
                  const std::string& action);
};

#endif
