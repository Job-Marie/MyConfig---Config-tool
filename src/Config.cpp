#include <Config/Config.hpp>
#include <Config/ConfigException.hpp>

#include <fstream>

namespace config {
    void Config::loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if(!file) throw ConfigException("Unable to open config file: " + filename);
        
        parse(file);
    }

    void Config::saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if(!file) throw ConfigException("Unable to write config file : " + filename);

        for(const auto& [sectionName, section] : data_) {
            file<< "[" << sectionName << "]\n";
            for(const auto& [key, value] : section) {
                file<< key << " = "<< value << "\n";
            }
            file<<"\n";
        }
    }

    bool Config::has(const std::string& section, const std::string& key) const {
        auto it = data_.find(section);
        if(it == data_.end()) return false;
        return it->second.find(key) != it->second.end();
    }
    std::string Config::getString(const std::string& section, const std::string& key, const std::string& defaultValue) const {
        if (!has(section,key)) return defaultValue;
        return data_.at(section).at(key);
    }

    int Config::getInt(const std::string& section, const std::string& key, int defaultValue) const {
        if(!has(section, key)) return defaultValue;
        return std::stoi(data_.at(section).at(key));
    }

    bool Config::getBool(const std::string& section, const std::string& key, bool defaultValue) const {
        if(!has(section, key)) return defaultValue;
        const auto& value = data_.at(section).at(key);
        if(value == "true" || value =="1") return true;
        if(value == "false" || value =="0") return false;
        throw ConfigException("Invalid Boolean value for " + section + "." + key);
        return 0;
    }

    void Config::set(const std::string& section, const std::string& key, const std::string& value) {
        data_[section][key] = value;
    }

    void Config::parse(std::istream& input) {
        // Parsing à venir
    }
}