cmake_minimum_required(VERSION 3.25)
project(lab2_GC)

set(CMAKE_CXX_STANDARD 20)
set(SDL2_INCLUDE_DIR C:/Users/caste/OneDrive/Documentos/SDL2-2.28.1/include)
set(SDL2_LIB_DIR C:/Users/caste/OneDrive/Documentos/SDL2-2.28.1/lib/x64)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(lab2_GC main.cpp src/Renderer.cpp src/Renderer.h src/Renderer.cpp)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)
