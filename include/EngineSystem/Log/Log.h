#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <fstream>
#include <stdarg.h>
#include <iomanip>
#include <ctime>
#include <Windows.h>

class Log
{
public:
    static enum SYSTEM {
        ENGINE,
        ASSETS,
        GAME,
        // COUNT  = 3
    };

private:
    std::ofstream engineSystemLogFile;
    std::ofstream assetsSystemLogFile;
    std::ofstream gameSystemLogFile;

    const std::string engineSystemLogFilePath = "engineSystemLog.txt";
    const std::string assetsSystemLogFilePath = "assetsSystemLog.txt";
    const std::string gameSystemLogFilePath = "gameSystemLog.txt";

public:
    static Log& getInstance();
    void init();
    void close();
    void write(SYSTEM arg, const char *msg, ...);

private:
    Log();
};


#endif
