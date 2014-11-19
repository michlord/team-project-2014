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

void Log::write(SYSTEM arg, const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    char szBuf[1024];
    vsprintf_s(szBuf, msg, args);

    SYSTEMTIME time;
    GetSystemTime(&time);
    char currentTime[100];
    sprintf_s(currentTime, 100, " [%d-%d-%d %d:%d:%d:%d]", time.wYear, time.wMonth, time.wDay,
              time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

    switch (arg) {
    case SYSTEM::ENGINE:
        engineSystemLogFile << szBuf << currentTime << std::endl;
        break;

    case SYSTEM::ASSETS:
        assetsSystemLogFile << szBuf << currentTime << std::endl;
        break;

    case SYSTEM::GAME:
        gameSystemLogFile << szBuf << currentTime << std::endl;
        break;
    }
}
