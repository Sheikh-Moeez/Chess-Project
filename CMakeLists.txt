cmake_minimum_required(VERSION 3.10)
project(Chess)

set(CMAKE_CXX_STANDARD 17)

# SFML package setup
find_package(SFML 2.6 REQUIRED graphics window system)

# Add your source files
file(GLOB SOURCES "src/*.cpp")

# Create the executable
add_executable(Chess ${SOURCES})

# Link SFML libraries
target_link_libraries(Chess sfml-graphics sfml-window sfml-system)

