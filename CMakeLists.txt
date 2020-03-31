cmake_minimum_required(VERSION 3.15)
project(Segmentation)

set(CMAKE_CXX_STANDARD 14)

cmake_minimum_required(VERSION 3.15)
project(IPAC_Excercises)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(OpenCV_DIR "C:\\OpenCV\\mingw-build\\install")
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

add_executable(exercises_01_a src/exercises_01_a.cpp)
add_executable(exercises_01_b src/exercises_01_b.cpp src/utils/utils.hpp)
add_executable(exercises_02_a src/exercises_02_a.cpp)
add_executable(exercises_02_b src/exercises_02_b.cpp)

# linking
target_link_libraries(exercises_01_a ${OpenCV_LIBS})
target_link_libraries(exercises_01_b ${OpenCV_LIBS})
target_link_libraries(exercises_02_a ${OpenCV_LIBS})
target_link_libraries(exercises_02_b ${OpenCV_LIBS})