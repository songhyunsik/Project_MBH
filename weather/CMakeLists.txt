cmake_minimum_required(VERSION 3.2)
project(basicOp)
find_package(CURL REQUIRED)
file(GLOB SOURCES "*.cpp")

set(GCC_COVERAGE_COMPILE_FLAGS "-fexec-charset=EUC-KR")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")



foreach(SOURCE ${SOURCES})
    get_filename_component(EXE_NAME ${SOURCE} NAME_WE)
    add_executable(${EXE_NAME} ${SOURCE})
    target_link_libraries(${EXE_NAME} ${CURL_LIBRARIES})
endforeach()
