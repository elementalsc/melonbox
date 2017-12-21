#ifndef MELONLOGGER_H
#define MELONLOGGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <chrono>

#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

enum LogLevel
{
    Info        = 0,
    Trace       = 1,
    Warning     = 2,
    Error       = 3,
    Fatal       = 4
};

class Progression;

// Singleton logger class
class MelonLogger
{
private:

    static MelonLogger* mInstance;
    std::ofstream mLogFile;
    std::string printLogLevel(LogLevel iLogLevel);
    std::string timestamp();
    bool mLoggingEnabled = true;
    MelonLogger();
    ~MelonLogger();

public:

    static MelonLogger* getInstance();
    MelonLogger(MelonLogger const&)     = delete;
    void operator=(MelonLogger const&)  = delete;

//=====================================================================================================================
// LOGGING FUNCTIONS
//=====================================================================================================================

    // Generic logging
    void log(std::string iLogString, LogLevel iLogLevel = Info);

    // Progression logging
    void logProgression(Progression& iProgression, std::string iPrefix = "");



}; // class MelonLogger

#endif // MELONLOGGER_H
