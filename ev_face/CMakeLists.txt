cmake_minimum_required(VERSION 2.8.0)

project(ev_face)

# Use C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

message(STATUS "C++11 support has been enabled by default.")

# Set include
include_directories(
            /usr/include
            /usr/local/include
            ./include
            /home/inory/SeetaFaceEngine/FaceDetection/include
            /home/inory/SeetaFaceEngine/FaceAlignment/include
            /home/inory/SeetaFaceEngine/FaceIdentification/include
            )

# Set libs
set(facedet_required_libs ${CMAKE_SOURCE_DIR}/lib/libseeta_facedet_lib.so)
list(APPEND facedet_required_libs ${CMAKE_SOURCE_DIR}/lib/libseeta_fa_lib.so)
list(APPEND facedet_required_libs ${CMAKE_SOURCE_DIR}/lib/libviplnet.so.4.5)

# Use OPENCV
find_package(OpenCV)
if (NOT OpenCV_FOUND)
    message(WARNING "OpenCV not found. Test will not be built.")
else()
    include_directories(${OpenCV_INCLUDE_DIRS})
    list(APPEND facedet_required_libs ${OpenCV_LIBS})
endif()

find_package(GLOG REQUIRED)

aux_source_directory(. EV_FACE_SRC)
aux_source_directory(./src EV_FACE_SRC)

add_executable(ev_face ${EV_FACE_SRC})
target_link_libraries(ev_face 
            ${facedet_required_libs}
            ${GLOG_LIBRARIES}
            )
