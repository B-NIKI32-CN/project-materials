cmake_minimum_required(VERSION 3.24) # FetchContent требует современную версию CMake
project(project-materials VERSION 0.1.0 LANGUAGES C CXX)

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
add_executable(project-materials main.cpp
               src/utils/functions/forse.cpp
               src/utils/particle_box.cpp
               src/utils/iterator.cpp
               src/core/settings/root.cpp
               src/core/settings/customs.cpp)

target_include_directories(project-materials PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}          # корень проекта
    ${CMAKE_CURRENT_SOURCE_DIR}/src      # чтобы "Headers/xxx.h" работало
    ${CMAKE_CURRENT_SOURCE_DIR}/Headers  # чтобы просто "xxx.h" работало
)


# Привязка графического и звукового модулей SFML к вашему проекту
target_link_libraries(project-materials PRIVATE
            SFML::Graphics
            SFML::Audio)

