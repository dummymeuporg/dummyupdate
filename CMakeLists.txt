cmake_minimum_required(VERSION 3.10.0)
project(dummyupdate)
include_directories(include vendor/libdummy/include)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} \
    -L${CMAKE_CURRENT_SOURCE_DIR}/vendor/libdummy/build \
    -lboost_filesystem -lboost_system -lboost_log -lpthread")
add_executable(dummyupdate
	src/main.cpp
	src/dummy/project.cpp
    src/project_content.cpp
	src/server.cpp
	src/session.cpp
	src/session/state.cpp
	src/session/initial_state.cpp
	src/session/send_files_state.cpp
	src/session/send_hashes_state.cpp
)

target_link_libraries(dummyupdate
    dummy
)
