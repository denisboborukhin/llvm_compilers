cmake_minimum_required(VERSION 3.16.3)

set(PROJECT_NAME log_pass)
project(${PROJECT_NAME} LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_COMPILER clang++-18)
set(CMAKE_C_COMPILER clang-18)

find_package(LLVM 18.1.8 REQUIRED)
find_package(SDL2 REQUIRED)

set(PASS_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(APP_SOURCE_DIR ${CMAKE_SOURCE_DIR}/../SDL/src)

add_library(log_pass SHARED ${PASS_SOURCE_DIR}/tracer_pass.cpp)
target_include_directories(log_pass PRIVATE ${LLVM_INCLUDE_DIRS})

add_library(app OBJECT ${APP_SOURCE_DIR}/app.c)
target_include_directories(app PRIVATE ${APP_INCLUDE_DIR})
target_compile_options(app PRIVATE -fPIC -O2 -fpass-plugin=./liblog_pass.so)
add_dependencies(app log_pass)

add_executable(app_trace
    ${PASS_SOURCE_DIR}/tracer.cpp
    ${APP_SOURCE_DIR}/start.c
    ${APP_SOURCE_DIR}/sim.c
    $<TARGET_OBJECTS:app>)
target_include_directories(app_trace PRIVATE
    ${APP_INCLUDE_DIR}
    ${LLVM_INCLUDE_DIRS})
target_link_libraries(app_trace PRIVATE SDL2 m LLVM)