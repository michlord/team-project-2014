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
        enum class System {
            Engine,
            Assets,
            Game,
            // Count  = 3
        };

        static Log& get();

        void write(System arg, const char *msg, ...);

    private:
        Log();
        ~Log();

        void init();
        void close();

        template <typename Duration>
        std::string getTime(tm t, Duration fraction);

        std::ofstream engineSystemLogFile;
        std::ofstream assetsSystemLogFile;
        std::ofstream gameSystemLogFile;

        static const std::string engineSystemLogFilePath;
        static const std::string assetsSystemLogFilePath;
        static const std::string gameSystemLogFilePath;

};

#endif
