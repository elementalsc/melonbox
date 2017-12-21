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

/*
    char buffer[30];
    struct timeval tv;

    time_t curtime;

    gettimeofday(&tv, NULL);
    curtime=tv.tv_sec;

    strftime(buffer,30,"%m-%d-%Y  %T.",localtime(&curtime));
    printf("%s%ld",buffer,tv.tv_usec);

    std::string oString = static_cast<std::string>(buffer) + " " + std::to_string(tv.tv_sec);

    return oString;
    //return std::to_string(buffer);// + " " + std::to_string(tv.tv_sec);
    //return static_cast<std::string>(buffer);
*/

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
