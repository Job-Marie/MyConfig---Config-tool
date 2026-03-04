#pragma once

#include<stdexcept>
#include<string>

namespace config {
    class ConfigException : public std::runtime_error {
        public:
        explicit ConfigException(const std::string& message);
    };
}