cmake_minimum_required(VERSION 4.0)

project(ConfigTool VERSION 1.0) #DESCRIPTION "Simple INI configuration library" LANGUAGE CXX

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
    src/ConfigParser.cpp
)

target_include_directories(configtool
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.2
)

FetchContent_MakeAvailable(Catch2)

# Executables tests
add_executable(configtool_tests
    tests/config_parse_tests.cpp
)

target_link_libraries(configtool_tests
    PRIVATE 
    configtool
    Catch2::Catch2WithMain
)

enable_testing()

add_test(NAME configtool_tests COMMAND config_tests)