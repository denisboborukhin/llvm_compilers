cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

project(SDL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_COMPILER clang++-18)
set(CMAKE_C_COMPILER clang-18)

find_package(SDL2 REQUIRED)

include_directories(./src)
add_library(sim src/sim.c)
target_link_libraries(sim PRIVATE SDL2)

set(APP_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SOURCES
    ${APP_SOURCES_DIR}/app.c
    ${APP_SOURCES_DIR}/start.c)

add_executable(app ${SOURCES})
target_link_libraries(app sim)

add_custom_target(run_app
    COMMAND ./app
)
add_dependencies(run_app app)

add_custom_target(gen_ir
    COMMAND ${CMAKE_C_COMPILER} -S -emit-llvm -O2 ${APP_SOURCES_DIR}/app.c -o app.ll
)

find_package(LLVM 18.1.8 REQUIRED)

set(APP_IR_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/IRGen)

add_custom_target(gen_app_ir
    COMMAND ${APP_IR_SOURCES_DIR}/app_ir_gen.sh
)

#### Attempts to invoke assembly via CMake
## first 
# set(IR_GEN_SOURCES
#     ${APP_SOURCES_DIR}/sim.c
#     ${APP_IR_SOURCES_DIR}/app_ir_gen.cpp
# )

# add_custom_command(
#     OUTPUT app_executable
#     COMMAND clang++-18
#     -I${APP_SOURCES_DIR}
#     -I${LLVM_INCLUDE_DIRS}
#     ${IR_GEN_SOURCES}
#     -lSDL2
#     -o app_executable
#     COMMENT "Compiling and linking app_executable"
# )
#
# add_custom_target(app_ir_gen DEPENDS app_executable)

## second
# add_executable(app_ir_gen ${IR_GEN_SOURCES})
# target_include_directories(app_ir_gen PRIVATE
#     ${APP_SOURCES_DIR}
#     ${LLVM_INCLUDE_DIRS})
# target_link_libraries(app_ir_gen PRIVATE SDL2 LLVM)