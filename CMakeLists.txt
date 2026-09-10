cmake_minimum_required(VERSION 3.24) # FetchContent требует современную версию CMake
project(sym VERSION 0.1.0 LANGUAGES C CXX)

# SFML 3.1.0 строго требует поддержку стандарта C++17
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Автоматическое скачивание и сборка SFML 3.1.0 с GitHub
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        3.1.0
)
FetchContent_MakeAvailable(SFML)

# Создание исполняемого файла из вашего main.cpp
add_executable(sym main.cpp
    Headers/forse.h
    Headers/root.h
    Headers/iterator.h)

# Привязка графического и звукового модулей SFML к вашему проекту
target_link_libraries(sym PRIVATE SFML::Graphics SFML::Audio)
