#include <EngineSystem/Log/Log.h>

const std::string Log::engineSystemLogFilePath = "engineSystemLog.txt";
const std::string Log::assetsSystemLogFilePath = "assetsSystemLog.txt";
const std::string Log::gameSystemLogFilePath = "gameSystemLog.txt";

Log::Log() {

}

Log::~Log() {
    close();
}

Log& Log::get() {
    static Log instance;
    return instance;
}

void Log::init() {
    engineSystemLogFile.open(engineSystemLogFilePath);
    if (!engineSystemLogFile.is_open())
        std::cerr << "Unable to open engineSystemLogFile" << std::endl;

    assetsSystemLogFile.open(assetsSystemLogFilePath);
    if (!assetsSystemLogFile.is_open())
        std::cerr << "Unable to open assetsSystemLogFile" << std::endl;

    gameSystemLogFile.open(gameSystemLogFilePath);
    if (!gameSystemLogFile.is_open())
        std::cerr << "Unable to open gameSystemLogFile" << std::endl;
}

void Log::close() {
    if(engineSystemLogFile.is_open())
        engineSystemLogFile.close();

    if(assetsSystemLogFile.is_open())
        assetsSystemLogFile.close();

    if(gameSystemLogFile.is_open())
        gameSystemLogFile.close();
}

template <typename Duration>
std::string Log::getTime(tm t, Duration fraction) {
    char buff[100];
    sprintf_s(buff, 100, " [%04u-%02u-%02u %02u:%02u:%02u:%03u]", t.tm_year + 1900,
        t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec,
        std::chrono::duration_cast<std::chrono::milliseconds>(fraction).count());
    std::string time = buff;
    return time;
}

void Log::write(System arg, const char *msg, ...) {
    static bool initialized = false;
    
    if(initialized == false) {
        init();
        initialized = true;
    }

    va_list args;
    va_start(args, msg);
    char szBuf[1024];
    vsprintf_s(szBuf, msg, args);

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::chrono::system_clock::duration tp = now.time_since_epoch();

    tp -= std::chrono::duration_cast<std::chrono::seconds>(tp);

    time_t tt = std::chrono::system_clock::to_time_t(now);
    tm local_tm;
    localtime_s(&local_tm, &tt);
    std::string currentTime = getTime(local_tm, tp);

    switch (arg) {
        case System::Engine:
            if(engineSystemLogFile.is_open())
                engineSystemLogFile << szBuf << currentTime.c_str() << std::endl;
            break;

        case System::Assets:
            if(assetsSystemLogFile.is_open())
                assetsSystemLogFile << szBuf << currentTime.c_str() << std::endl;
            break;

        case System::Game:
            if(gameSystemLogFile.is_open())
                gameSystemLogFile << szBuf << currentTime.c_str() << std::endl;
            break;
    }
}

