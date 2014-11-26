#ifndef ENGINE_SYSTEM_CONFIG_CONFIG_H_INCLUDED
#define ENGINE_SYSTEM_CONFIG_CONFIG_H_INCLUDED

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Config {
    public:
        static Config& Get();

        void load(std::string fileName);
        void save(std::string fileName);
        std::string getString(std::string section, std::string key, std::string defaultValue);
        int getInt(std::string section, std::string key, int defaultValue);
        float getFloat(std::string section, std::string key, float defaultValue);
        void set(std::string section, std::string key, std::string value);

    private:
        std::vector <std::pair<std::string, std::string>> settings;
        Config();
};

#endif