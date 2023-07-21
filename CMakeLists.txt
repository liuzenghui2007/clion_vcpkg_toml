cmake_minimum_required(VERSION 3.25)
project(untitled)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/home/zenghui/Qt/5.15.2/gcc_64/lib/cmake/Qt5")

find_package(Qt5 COMPONENTS
        Core
        REQUIRED)
find_package(glog CONFIG REQUIRED)
if (glog_FOUND)
    message("find glog=${glog_VERSION}")
endif ()
find_package(toml11 REQUIRED)
if (toml11_FOUND)
    message("find toml11=${toml11_VERSION}")
endif ()
find_package(gRPC REQUIRED)
if (gRPC_FOUND)
    message("find gRPC=${gRPC_VERSION}")
endif ()
find_package(OpenCV REQUIRED)
if (OpenCV_FOUND)
    message("find OpenCV=${OpenCV_VERSION}")
endif ()
find_package(libusb REQUIRED)
if (libusb_FOUND)
    message("find libusb=${libusb_VERSION}")
endif ()

add_executable(untitled main.cpp)
target_link_libraries(untitled
        Qt5::Core
        )
target_link_libraries(untitled glog::glog)
find_package(toml11 CONFIG REQUIRED)
target_link_libraries(untitled toml11::toml11)

# Add the custom command to copy the file "example.toml" to the build output directory
add_custom_command(TARGET untitled POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/example.toml
        ${CMAKE_BINARY_DIR}/example.toml)