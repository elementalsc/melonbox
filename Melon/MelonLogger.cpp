#include "MelonLogger.h"

MelonLogger* MelonLogger::mInstance = nullptr;

MelonLogger*
MelonLogger::getInstance()
{
    if(!mInstance)
    {
        mInstance = new MelonLogger();
    }

    return mInstance;
}

MelonLogger::MelonLogger()
{
    mLogFile.open("MelonLog.txt");
}

MelonLogger::~MelonLogger()
{
    if(mInstance)
    {
        mLogFile.close();
        delete mInstance;
    }
}

std::string
MelonLogger::printLogLevel(LogLevel iLogLevel)
{
    switch(iLogLevel)
    {
    case Info:      return "INFO  :"; break;
    case Trace:     return "TRACE :"; break;
    case Warning:   return "WARN  :"; break;
    case Error:     return "ERROR :"; break;
    case Fatal:     return "FATAL :"; break;
    default :       return "LOGERROR :"; break;
    }
}

void
MelonLogger::log(std::string iLogString, LogLevel iLogLevel)
{
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    mLogFile << std::put_time(std::localtime(&now), "%F %T")
             << "\t"
             << printLogLevel(iLogLevel)
             << "\t"
             << iLogString;
}
