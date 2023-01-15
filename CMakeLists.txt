cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20 GLOBAL)

project(BaseDX11App LANGUAGES CXX VERSION 0.0.1)

include(cmake/AsyncLogger.cmake)

file(GLOB_RECURSE SRC_FILES
    "${PROJECT_SOURCE_DIR}/src/**.cpp"
    "${PROJECT_SOURCE_DIR}/src/**.hpp"
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_precompile_headers(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/src/common.hpp")
target_link_libraries(${PROJECT_NAME} AsyncLogger)
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/src/")