cmake_minimum_required(VERSION 3.16)

project(Viper VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Curses REQUIRED)

add_executable(Viper
    src/main.cpp
    src/App.cpp
    src/Game.cpp
    src/Renderer.cpp
    src/HighScore.cpp
    src/Snake.cpp
)

target_include_directories(Viper PRIVATE include ${CURSES_INCLUDE_DIR})
target_link_libraries(Viper PRIVATE ${CURSES_LIBRARIES})

if(MSVC)
    target_compile_options(Viper PRIVATE /W4)
else()
    target_compile_options(Viper PRIVATE -Wall -Wextra -Wpedantic)
endif()
