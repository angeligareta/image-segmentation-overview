cmake_minimum_required(VERSION 3.15)
project(Segmentation)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(OpenCV_DIR "/home/angeliton/installation/OpenCV-master/lib/cmake/opencv4")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

add_executable(exercises_011_a src/exercises_011_a_flatzone.cpp src/utils/utils.hpp)
add_executable(exercises_013_a src/exercises_013_a_minimum.cpp src/utils/utils.hpp)
add_executable(exercises_013_b src/exercises_013_b_maximum.cpp src/utils/utils.hpp)

# linking
target_link_libraries(exercises_011_a ${OpenCV_LIBS})
target_link_libraries(exercises_013_a ${OpenCV_LIBS})
target_link_libraries(exercises_013_b ${OpenCV_LIBS})