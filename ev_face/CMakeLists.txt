cmake_minimum_required(VERSION 2.8.0)

project(ev_face)

# Use C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "C++11 support has been enabled by default.")

include_directories(include)

# Set seetaface include
set(src_directory 
    /home/inory/SeetaFaceEngine/FaceDetection/include
    )
list(APPEND src_directory /home/inory/SeetaFaceEngine/FaceAlignment/include)
list(APPEND src_directory /home/inory/SeetaFaceEngine/FaceIdentification/include)
include_directories(${src_directory})

# Set seetaface libs
set(facedet_required_libs /home/inory/SeetaFaceEngine/FaceDetection/build/libseeta_facedet_lib.so)
list(APPEND facedet_required_libs /home/inory/SeetaFaceEngine/FaceAlignment/build/libseeta_fa_lib.so)
list(APPEND facedet_required_libs /home/inory/SeetaFaceEngine/FaceIdentification/build/libviplnet.so)

# Use OPENCV
find_package(OpenCV)
if (NOT OpenCV_FOUND)
    message(WARNING "OpenCV not found. Test will not be built.")
else()
    include_directories(${OpenCV_INCLUDE_DIRS})
    list(APPEND facedet_required_libs ${OpenCV_LIBS})
endif()

add_executable(ev_face ./main.cpp)
target_link_libraries(ev_face ${facedet_required_libs})
