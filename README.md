# ConfigTool

ConfigTool is a lightweight C++ library for reading and writing configuration files in **INI format**.

The goal of this project is to practice modern C++ development practices including:

* modular architecture
* unit testing
* parsing text files
* error handling
* Test-Driven Development (TDD)

---

## Features

* Parse INI configuration files
* Support for sections and key-value pairs
* Trim whitespace automatically
* Read values as:
  * string
  * integer
  * boolean
* Default values for missing keys
* Save configuration back to file
* Unit tests with Catch2

Example supported configuration:

```
[graphics]
width = 1280
height = 720
fullscreen = true

[audio]
volume = 80
```

---

## Example Usage

```cpp
#include <Config/Config.hpp>

config::Config cfg;

cfg.loadFromFile("config.ini");

int width = cfg.getInt("graphics", "width", 800);
bool fullscreen = cfg.getBool("graphics", "fullscreen", false);
```

---

## Project Structure

```
ConfigTool
│
├── include/
│   └── Config/
│       ├── Config.hpp
│       ├── ConfigParser.hpp
│       └── ConfigException.hpp
│
├── src/
│   ├── Config.cpp
│   └── ConfigParser.cpp
│
├── tests/
│   └── config_parse_tests.cpp
│
└── CMakeLists.txt
```

---

## Running Tests

The project uses Catch2 for unit testing.

Build the project:

```
cmake -S . -B build
cmake --build build
```

Run tests:

```
ctest --test-dir build
```

---

## Learning Goals

This project focuses on:

* designing a small reusable C++ library
* separating parsing logic from API
* writing unit tests before implementation
* using `std::istream` to simplify testing but work with files loading too
* support for comments (`#` and `;`)

---

## Future Improvements

Possible extensions:

* environment variable substitution
* nested configuration structures
* better error reporting
* performance improvements

---