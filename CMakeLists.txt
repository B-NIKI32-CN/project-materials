cmake_minimum_required(VERSION 3.24) 
project(project-materials VERSION 0.1.0 LANGUAGES C CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)




add_executable(project-materials main.cpp
               src/utils/functions/forse.cpp
               src/utils/functions/heat_dissipation.cpp
               src/utils/particle_box.cpp
               src/utils/iterator.cpp
               src/core/settings/root.cpp
               src/core/settings/customs.cpp)

target_include_directories(project-materials PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}      
    ${CMAKE_CURRENT_SOURCE_DIR}/src  
    ${CMAKE_CURRENT_SOURCE_DIR}/Headers
)



target_link_libraries(project-materials PRIVATE
            SFML::Graphics
            SFML::Window
            SFML::System)

