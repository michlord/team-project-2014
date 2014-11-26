#ifndef ENGINE_SYSTEM_LOG_LOG_H_INCLUDED
#define ENGINE_SYSTEM_LOG_LOG_H_INCLUDED

#include <iostream>
#include <fstream>
#include <stdarg.h>
#include <iomanip>
#include <ctime>
#include <chrono>

class Log {
    public:
        enum SYSTEM {
            ENGINE,
            ASSETS,
            GAME,
            // COUNT  = 3
        };

        static Log& getInstance();
        void init();
        void close();
        void write(SYSTEM arg, const char *msg, ...);

    private:
        std::ofstream engineSystemLogFile;
        std::ofstream assetsSystemLogFile;
        std::ofstream gameSystemLogFile;

        static const std::string engineSystemLogFilePath;
        static const std::string assetsSystemLogFilePath;
        static const std::string gameSystemLogFilePath;

        Log();
};

#endif
