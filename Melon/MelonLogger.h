#ifndef MELONLOGGER_H
#define MELONLOGGER_H


class MelonLogger
{
private:

    static MelonLogger* mInstance;
    MelonLogger(){};

public:

    static MelonLogger* getInstance();
    MelonLogger(MelonLogger const&)     = delete;
    void operator=(MelonLogger const&)  = delete;


};

#endif // MELONLOGGER_H
