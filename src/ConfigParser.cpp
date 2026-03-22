#include "Config/ConfigParser.hpp"

#include <fstream>
#include<sstream>
#include<algorithm>

namespace config {

    std::string ConfigParser::trim(const std::string& s) {
        auto start = std::find_if_not(s.begin(), s.end(), ::isspace);
        auto end   = std::find_if_not(s.rbegin(), s.rend(), ::isspace).base();
        return (start < end ? std::string(start, end) : "");
    }

    bool ConfigParser::load(const std::string& filename) {
        std::ifstream file(filename);
        if(!file.is_open()) return false;

        std::string line;
        std::string currentSection;

        while(std::getline(file, line)) {
            // gestion des commentaires avec # et  ;
            auto commentpos = line.find_first_of("#;");
            if(commentpos != std::string::npos) line = line.substr(0, commentpos);  // on ignore les charactères après commentpos

            line = trim(line);
            if(line.empty()) continue;

            if(line.front() == '[' && line.back() == ']') {
                currentSection = trim(line.substr(1, line.size() -2));
            } else {
                std::stringstream ss(line);
                std::string key, value;
                if(std::getline(ss, key, '=') && std::getline(ss, value)) {
                    data[currentSection][trim(key)] = trim(value);
                }
            }
        }
        return true;
    }

    bool ConfigParser::load(std::istream& input) {
        std::string line;
        std::string currentSection;

        while(std::getline(input, line)) {
            // gestion des commentaires avec # et ;
            auto commentpos = line.find_first_of("#;");
            if(commentpos != std::string::npos) line = line.substr(0, commentpos);  // on ignore les charactères après commentpos

            line = trim(line);
            if(line.empty()) continue;

            if(line.front() == '[' && line.back() == ']') {
                currentSection = trim(line.substr(1, line.size() -2));
            } else {
                std::stringstream ss(line);
                std::string key, value;
                if(std::getline(ss, key, '=') && std::getline(ss, value)) {
                    data[currentSection][trim(key)] = trim(value);
                }
            }
        }
        return true;
    }

    config_table ConfigParser::get_data() {
            return data;
        }

    std::string ConfigParser::get(const std::string& section, const std::string& key) const {
        auto sec = data.find(section);
        if(sec != data.end()) {
            auto k = sec->second.find(key);
            if(k != sec->second.end()) {
                return k->second;
            }
        }
        return "";
    }
}