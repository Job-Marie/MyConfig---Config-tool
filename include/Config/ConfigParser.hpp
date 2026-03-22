#pragma once

#include <string>
#include <unordered_map>

using config_table = std::unordered_map<std::string, std::unordered_map<std::string, std::string>>;

namespace config {
    class ConfigParser {
        config_table data;
        public:
        std::string trim(const std::string& s);
        bool load(const std::string& filename);
        bool load(std::istream& input);
        config_table get_data();
        std::string get(const std::string& section, const std::string& key) const;
    };
}