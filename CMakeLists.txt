cmake_minimum_required(VERSION 3.10)
project(StuScoreSys)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/Src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/Include"
)

# ========== 中文乱码修复 ==========
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
else()
    # MinGW: 源码 UTF-8，执行输出 UTF-8
    target_compile_options(${PROJECT_NAME} PRIVATE -fexec-charset=GBK)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
