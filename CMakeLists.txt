cmake_minimum_required(VERSION 3.25)
project(untitled)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/home/zenghui/Qt/5.15.2/gcc_64/lib/cmake/Qt5")
#set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -lpthread")
#set_target_properties(${TARGET} PROPERTIES
#        COMPILE_FLAGS "-pthread"
#        LINK_FLAGS "-pthread")

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
if (LIBUSB_FOUND)
    message("find libusb=${Libusb_VERSION}")
#    LIBUSB_LIBRARIES 是一个列表
endif ()

add_executable(untitled main.cpp usb_info.h usb_info.cpp)



target_link_libraries(untitled
        Qt5::Core
        )
# 包含头文件
target_include_directories(untitled PRIVATE ${LIBUSB_INCLUDE_DIRS})
# 链接glog
target_link_libraries(untitled glog::glog)
# 链接toml11
target_link_libraries(untitled toml11::toml11)
# 链接libusb
target_link_libraries(untitled ${LIBUSB_LIBRARIES})
# 链接grpc
target_link_libraries(untitled gRPC::gpr gRPC::grpc gRPC::grpc++ gRPC::grpc++_alts)
# 链接opencv
target_link_libraries(untitled opencv_ml opencv_dnn opencv_core opencv_flann)

# Add the custom command to copy the file "example.toml" to the build output directory
add_custom_command(TARGET untitled POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/example.toml
        ${CMAKE_BINARY_DIR}/example.toml)