cmake_minimum_required(VERSION 3.31)
project(W2Uploader)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "utils/x64" "utils/x86")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug build")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__DEBUG")
    add_definitions(-DCSERIALPORT_DEBUG)
endif ()

find_package(CSerialPort REQUIRED)

set(EXECUTABLE_NAME "w2uploader")
add_executable(${EXECUTABLE_NAME} main.cpp)
include_directories(${CSerialPort_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} ${CSerialPort_LIBRARY}
        -static-libgcc -static-libstdc++
        -Wl,-Bstatic -lstdc++ -lpthread
        -Wl,-Bdynamic)
