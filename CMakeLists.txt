cmake_minimum_required(VERSION 3.20)

project(ConfigTool VERSION 1.0 DESCRIPTION "Simple INI configuration library" LANGUAGE CXX)

# Standard C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Warnings
if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpendantic)
endif()

# Library
add_library(configtool
    src/Config.cpp
    src/ConfigException.cpp
)

target_include_directories(configtool
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# Executables tests
add_executable(configtool_tests
    tests/main.cpp
)

target_link_libraries(configtool_tests
    PRIVATE configtool
)