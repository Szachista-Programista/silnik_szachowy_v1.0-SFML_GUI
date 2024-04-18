include_directories("C:/Path/to/the/SFML/include")

cmake_minimum_required(VERSION 3.10)
project(ChessEngine_SFML_Interface)
find_package(SFML REQUIRED COMPONENTS graphics window system)

file(GLOB_RECURSE SOURCES "src/*.cpp")
list(APPEND SOURCES "main.cpp")

add_executable(MyExecutable ${SOURCES})

target_link_libraries(MyExecutable sfml-graphics sfml-window sfml-system)
