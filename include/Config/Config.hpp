#pragma once

#include<string>
#include<unordered_map>
#include<istream>

namespace config {
    class Config {
        private :
        std::unordered_map <std::string, std::unordered_map <std::string, std::string>> data_;

        
        public :
        void parse(std::istream& input);
        void loadFromFile(const std::string& filename);
        void saveToFile(const std::string& filename) const;
        bool has(const std::string& section, const std::string& key) const;
        // getter for string, integer and bool
        std::string getString(const std::string& section, const std::string& key, const std::string& defaultValue = "") const;
        int getInt(const std::string& section, const std::string& key, const int defaultValue = 0) const;
        bool getBool(const std::string& section, const std::string& key, const bool defaultValue = false) const;
        // setter
        void set(const std::string& section, const std::string& key, const std::string& value);
    };
}