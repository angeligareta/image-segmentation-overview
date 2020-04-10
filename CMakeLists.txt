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

add_executable(exercises_01_a_contour_extraction src/exercises_01_a_contour_extraction.cpp)
add_executable(exercises_01_b_grassfire src/exercises_01_b_grassfire.cpp src/utils/utils.hpp)
add_executable(exercises_02_a_wheel_teeth_count src/exercises_02_a_wheel_teeth_count.cpp)
add_executable(exercises_02_b_watershed src/exercises_02_b_watershed.cpp)
add_executable(exercises_11_a_flatzone src/exercises_11_a_flatzone.cpp src/utils/utils.hpp)
add_executable(exercises_13_a_minimum src/exercises_13_a_minimum.cpp src/utils/utils.hpp)
add_executable(exercises_13_b_maximum src/exercises_13_b_maximum.cpp src/utils/utils.hpp)

# linking
target_link_libraries(exercises_01_a_contour_extraction ${OpenCV_LIBS})
target_link_libraries(exercises_01_b_grassfire ${OpenCV_LIBS})
target_link_libraries(exercises_02_a_wheel_teeth_count ${OpenCV_LIBS})
target_link_libraries(exercises_02_b_watershed ${OpenCV_LIBS})
target_link_libraries(exercises_11_a_flatzone ${OpenCV_LIBS})
target_link_libraries(exercises_13_a_minimum ${OpenCV_LIBS})
target_link_libraries(exercises_13_b_maximum ${OpenCV_LIBS})