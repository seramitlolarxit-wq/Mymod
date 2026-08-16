cmake_minimum_required(VERSION 3.22.1)
project(mycheat)

include(FetchContent)
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui
  GIT_TAG        v1.89
)
FetchContent_MakeAvailable(imgui)

# Указываем точный путь к твоему файлу с большой буквы
add_library(mycheat SHARED app/src/main/jni/Main/Main.cpp)

target_include_directories(mycheat PRIVATE 
    ${imgui_SOURCE_DIR} 
    app/src/main/jni/Main/
)

target_link_libraries(mycheat android log)
