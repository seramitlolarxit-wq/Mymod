cmake_minimum_required(VERSION 3.22.1)
project(mycheat)

include(FetchContent)
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui
  GIT_TAG        v1.89
)
FetchContent_MakeAvailable(imgui)

# Автоматически ищем все .cpp файлы во всех папках проекта
file(GLOB_RECURSE SRC_FILES *.cpp)

add_library(mycheat SHARED ${SRC_FILES})

target_include_directories(mycheat PRIVATE 
    ${imgui_SOURCE_DIR}
    app/src/main/jni/Main
)

target_link_libraries(mycheat android log)
