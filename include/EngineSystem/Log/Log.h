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
    enum SYSTEM {
        ENGINE,
        ASSETS,
        GAME,
        // COUNT  = 3
    };

private:
    std::ofstream engineSystemLogFile;
    std::ofstream assetsSystemLogFile;
    std::ofstream gameSystemLogFile;

    static const std::string engineSystemLogFilePath;
    static const std::string assetsSystemLogFilePath;
    static const std::string gameSystemLogFilePath;

public:
    static Log& getInstance();
    void init();
    void close();
    void write(SYSTEM arg, const char *msg, ...);

private:
    Log();
};


#endif
