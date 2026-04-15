cmake_minimum_required(VERSION 3.10)
project(HideAndSeekGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native")

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

add_executable(HideAndSeek ${SOURCES} ${HEADERS})

add_definitions(-finput-charset=UTF-8 -fexec-charset=UTF-8)

target_link_libraries(HideAndSeek sfml-graphics sfml-window sfml-system sfml-audio)


target_include_directories(HideAndSeek PUBLIC include)