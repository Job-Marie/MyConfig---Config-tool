#include "Config/ConfigException.hpp"

namespace config {
    ConfigException::ConfigException(const std::string& message) : std::runtime_error(message) {

    }
}