include_directories(  "D:/PROGRAMY/SFML/SFML/include")
# link_directories(     "D:/PROGRAMY/SFML/SFML/lib")


cmake_minimum_required(VERSION 3.10)
project(ChessEngine_SFML_Interface)
find_package(SFML REQUIRED COMPONENTS graphics window system)

file(GLOB_RECURSE SOURCES "src/*.cpp")
list(APPEND SOURCES "main.cpp")

add_executable(MyExecutable ${SOURCES})

target_link_libraries(MyExecutable sfml-graphics sfml-window sfml-system)
