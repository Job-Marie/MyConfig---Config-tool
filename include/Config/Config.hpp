#pragma once

#include<string>
#include<unordered_map>
using namespace std;

class Config {
    private :
    unordered_map <string, unordered_map <string, string>> data_;

    public :
    void loadFromFile(const string& filename);
    void saveToFile(const string& filename);
    bool has(const string& section, const string& key) const;
    // getter for string, integer and bool
    string getString(const string& section, const string& key, const string& defaultValue = "") const;
    int getInt(const string& section, const string& key, const int defaultValue = 0) const;
    bool getBool(const string& section, const string& key, const bool defaultValue = false) const;
    // setter
    void set(const string& section, const string& key, const string& value);
};