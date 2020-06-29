cmake_minimum_required(VERSION 3.7)

project(micasa
		VERSION 2.0
		LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

file(GLOB_RECURSE FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*")

add_executable(micasa "main.cpp" "${FILES}")
target_link_libraries(micasa Qt5::Widgets)
