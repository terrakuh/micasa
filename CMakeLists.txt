cmake_minimum_required(VERSION 3.7)

project(micasa
		VERSION 2.0
		LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type." FORCE)
endif()

find_package(Qt5 REQUIRED COMPONENTS Widgets)

file(GLOB_RECURSE FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*")

add_executable(micasa "main.cpp" "${FILES}")
target_link_libraries(micasa Qt5::Widgets)

install(TARGETS micasa
		RUNTIME DESTINATION "bin")
install(FILES "settings.json"
		DESTINATION "/etc"
		RENAME "micasa.json")
