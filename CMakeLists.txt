cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(PrettyRoutine)

set(PROJECT_SOURCES
	json11.cpp
	PrettyRoutine.cpp
	Tester.cpp
)

set(PROJECT_HEADERS
	json11.hpp
	PrettyRoutine.hpp
)

add_executable(PrettyRoutine ${PROJECT_HEADERS} ${PROJECT_SOURCES})