#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger
{
public:
    static void logDebug(const std::string &func, int errorCode, const std::string &detail);
    static std::string getErrorMsg(int errorCode);
};

#endif
