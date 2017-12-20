#ifndef MELONLOGGER_H
#define MELONLOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <chrono>

enum LogLevel
{
    Info        = 0,
    Trace       = 1,
    Warning     = 2,
    Error       = 3,
    Fatal       = 4
};

struct LogEntry
{
    time_t      mTimestamp;
    LogLevel    mLogLevel;
    std::string      mLogMessage;
};

class MelonLogger
{
private:

    static MelonLogger* mInstance;
    std::ofstream mLogFile;
    std::string printLogLevel(LogLevel iLogLevel);
    MelonLogger();
    ~MelonLogger();


public:

    static MelonLogger* getInstance();
    MelonLogger(MelonLogger const&)     = delete;
    void operator=(MelonLogger const&)  = delete;
    void log(std::string iLogString, LogLevel iLogLevel = Info);

}; // class MelonLogger

#endif // MELONLOGGER_H
