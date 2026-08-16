cmake_minimum_required(VERSION 3.22.1)
project(mycheat)

include(FetchContent)
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui
  GIT_TAG        v1.89
)
FetchContent_MakeAvailable(imgui)

# Файлы main.cpp и Offsets.h лежат прямо здесь, в корне
add_library(mycheat SHARED main.cpp)

target_include_directories(mycheat PRIVATE 
    ${imgui_SOURCE_DIR}
)

target_link_libraries(mycheat android log)
