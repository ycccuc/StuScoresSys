# 指定最低 CMake 版本
cmake_minimum_required(VERSION 3.10)

# 项目名称和语言
project(StuScoresSys VERSION 1.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 收集所有源文件（从 Src 目录）
file(GLOB_RECURSE SOURCES 
    "${CMAKE_SOURCE_DIR}/Src/*.cpp"
)

# 添加可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 指定头文件搜索路径（Include 目录）
target_include_directories(${PROJECT_NAME} PRIVATE 
    "${CMAKE_SOURCE_DIR}/Include"
)

# 编译选项（可选，但推荐开启）
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# 设置可执行文件输出目录
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)