#include <EngineSystem/Log/Log.h>

const std::string Log::engineSystemLogFilePath = "engineSystemLog.txt";
const std::string Log::assetsSystemLogFilePath = "assetsSystemLog.txt";
const std::string Log::gameSystemLogFilePath = "gameSystemLog.txt";

Log::Log() {

}

Log& Log::getInstance() {
    static Log instance;
    return instance;
}

void Log::init() {
    engineSystemLogFile.open(engineSystemLogFilePath);
    if (!engineSystemLogFile.is_open()) {
        std::cout << "Unable to open engineSystemLogFile" << std::endl;
        return;
    }

    assetsSystemLogFile.open(assetsSystemLogFilePath);
    if (!assetsSystemLogFile.is_open()) {
        std::cout << "Unable to open assetsSystemLogFile" << std::endl;
        return;
    }

    gameSystemLogFile.open(gameSystemLogFilePath);
    if (!gameSystemLogFile.is_open()) {
        std::cout << "Unable to open gameSystemLogFile" << std::endl;
        return;
    }
}

void Log::close() {
    engineSystemLogFile.close();
    assetsSystemLogFile.close();
    gameSystemLogFile.close();
}

template <typename Duration>
std::string getTime(tm t, Duration fraction) {
    char buff[100];
    sprintf_s(buff, 100, " [%04u-%02u-%02u %02u:%02u:%02u:%03u]", t.tm_year + 1900,
        t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec,
        std::chrono::duration_cast<std::chrono::milliseconds>(fraction).count());
    std::string time = buff;
    return time;
}

void Log::write(SYSTEM arg, const char *msg, ...) {
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
    case SYSTEM::ENGINE:
        engineSystemLogFile << szBuf << currentTime.c_str() << std::endl;
        break;

    case SYSTEM::ASSETS:
        assetsSystemLogFile << szBuf << currentTime.c_str() << std::endl;
        break;

    case SYSTEM::GAME:
        gameSystemLogFile << szBuf << currentTime.c_str() << std::endl;
        break;
    }
}

