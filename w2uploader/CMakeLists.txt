cmake_minimum_required(VERSION 3.31)

project(w2uploader)

set(CMAKE_CXX_STANDARD 11)
set(BUILD_SHARED_LIBS OFF)
set(CSerialPortRootPath "${CMAKE_CURRENT_SOURCE_DIR}/CSerialPort")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug build")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__DEBUG")
    add_definitions(-DCSERIALPORT_DEBUG)
endif ()

add_subdirectory(${CSerialPortRootPath})

add_executable(${PROJECT_NAME} main.cpp)
include_directories(${CSerialPortRootPath}/include)
target_link_libraries(${PROJECT_NAME} libcserialport)

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin)
