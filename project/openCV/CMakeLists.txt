cmake_minimum_required(VERSION 3.5)
project(TextExtraction)

find_package(OpenCV REQUIRED)
find_package(Tesseract REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} ${Tesseract_INCLUDE_DIRS})
add_executable(TextExtraction main.cpp)

target_link_libraries(TextExtraction ${OpenCV_LIBS} ${Tesseract_LIBRARIES})
