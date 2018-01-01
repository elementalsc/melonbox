#include "MelonLogger.h"
#include "Progression.h"

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
    //mLogFile.open("MelonLog.txt", std::ofstream::out | std::ofstream::app);
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

std::string MelonLogger::timestamp()
{

    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}

void
MelonLogger::log(std::string iLogString, LogLevel iLogLevel)
{
    if(mLoggingEnabled)
    {
        char * tm[80];
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        //mLogFile << std::put_time(std::localtime(&now), "%F %T")
        mLogFile << timestamp()
                 << " "
                 << printLogLevel(iLogLevel)
                 << " "
                 << iLogString
                 << std::endl;
    }
}

void
MelonLogger::logProgression(Progression& iProgression, std::string iPrefix)
{
    if(mLoggingEnabled)
    {
        std::string wLogMessage = iPrefix;

        wLogMessage.append(" ");
        wLogMessage.append(iProgression.toString());

        log(wLogMessage,Trace);
    }
}
