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

}


MelonLogger::~MelonLogger()
{
    if(mInstance)
    {
        delete mInstance;
    }
}
