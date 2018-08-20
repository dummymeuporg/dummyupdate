cmake_minimum_required(VERSION 3.10.0)
project(dummyupdate)
include_directories(include)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lboost_filesystem -lboost_system")
add_executable(dummyupdate
	src/main.cpp
	src/dummy/project.cpp
)
