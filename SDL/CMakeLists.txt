cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

set(PROJECT_NAME SDL)
project(${PROJECT_NAME} LANGUAGES C)

enable_language(C)
set(CMAKE_C_COMPILER clang)

include_directories(./src)
add_library(sim STATIC src/sim.c)
target_link_options(sim PUBLIC -lSDL2)

set(APP_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SOURCES
    ${APP_SOURCES_DIR}/app.c
    ${APP_SOURCES_DIR}/start.c)

add_executable (app ${SOURCES})
target_link_libraries(app sim)

add_custom_target (run_app
    COMMAND ./app
)
add_dependencies (run_app app)

add_custom_target(gen_ir
    COMMAND ${CMAKE_C_COMPILER} -S -emit-llvm -O2 ${APP_SOURCES_DIR}/app.c -o app.ll
)
