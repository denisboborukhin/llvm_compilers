cmake_minimum_required(VERSION 3.16.3)

set(PROJECT_NAME log_pass)
project(${PROJECT_NAME} LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)

find_package(LLVM REQUIRED)
if(NOT LLVM_FOUND)
  return()
endif()

include_directories(${LLVM_INCLUDE_DIR})

add_compile_options(-fPIC)
add_library(log_pass SHARED ./src/log_pass.cpp)

# set(CALLBACKS ${CMAKE_CURRENT_SOURCE_DIR}/Callbacks.cpp)
# add_custom_target(Callbacks ALL
#   COMMAND clang++ -std=c++20 -O2 ${CALLBACKS} -fPIC -c -o Callbacks.o
#   COMMENT "Generating callbacks" VERBATIM
#                   )

set(APP_SOURCES_DIR ${CMAKE_SOURCE_DIR}/../SDL/src)
set(SOURCES 
        ./src/log.cpp
        ${APP_SOURCES_DIR}/app.c
        ${APP_SOURCES_DIR}/start.c
    )

include_directories(${APP_SOURCES_DIR})
add_library(sim STATIC ${APP_SOURCES_DIR}/sim.c)
target_link_options(sim PUBLIC -lSDL2)

add_compile_options(-O2 -fpass-plugin=./liblog_pass.so) 
add_executable(app_log ${SOURCES})
target_link_libraries(app_log PUBLIC sim)
add_dependencies(app_log log_pass sim)