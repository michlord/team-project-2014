#include <EngineSystem/Config/Config.h>

Config::Config() {

}

Config& Config::Get() {
    static Config instance;
    //instance.load();
    return instance;
}

void Config::load(std::string fileName) {
    std::ifstream configFile;
    configFile.open(fileName.c_str(), std::ios::in);

    if (!configFile.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        return;
    }

    std::string section, line;
    std::string key, value;

    while (getline(configFile, line)) {
        int index = line.find("=");

        if (size_t(index) == std::string::npos) {
            section = line.substr(1, line.size() - 2);
            continue;
        }

        key = section + ":" + line.substr(0, index);
        value = line.substr(index + 1, line.size() - 1);

        settings.push_back(std::make_pair(key, value));
	}

    configFile.close();
}

void Config::save(std::string fileName) {
    std::ofstream configFile;
    configFile.open(fileName.c_str(), std::ios::out);

    if (!configFile.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        return;
    }

    std::string prevSection = "", currentSection, key, value;

    for (auto it = settings.begin(); it != settings.end(); it++) {
        int index = it->first.find(":");
        currentSection = it->first.substr(0, index);
        key = it->first.substr(index + 1, it->first.size() - 1);
        value = it->second;

        if (currentSection != prevSection) {
            configFile << "[" << currentSection << "]" << std::endl;
            prevSection = currentSection;
        }

        configFile << key << "=" << value << std::endl; 
    }

    configFile.close();
}

std::string Config::getString(std::string section, std::string key, std::string defaultValue) {
    auto it = settings.begin();
    while (it != settings.end() && it->first != (section + ":" + key)) it++;

    if (it == settings.end()) return defaultValue;

    return it->second;
}

int Config::getInt(std::string section, std::string key, int defaultValue) {
    std::string strRes = getString(section, key, "unknown");
    if (strRes == "unknown") return defaultValue;

    std::istringstream iss(strRes);
    int x;
    iss >> x;
    return x;
}

float Config::getFloat(std::string section, std::string key, float defaultValue) {
    std::string strRes = getString(section, key, "unknown");
    if (strRes == "unknown") return defaultValue;

    std::istringstream iss(strRes);
    float x;
    iss >> x;
    return x;
}

void Config::set(std::string section, std::string key, std::string value) {
    auto it = settings.begin();
    while (it != settings.end() && it->first != (section + ":" + key)) it++;

    if (it == settings.end()) return;

    it->second = value;
}

