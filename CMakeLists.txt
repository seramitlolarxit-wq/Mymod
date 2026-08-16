cmake_minimum_required(VERSION 3.22.1)
project(mycheat)

include(FetchContent)
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui
  GIT_TAG        v1.89
)
FetchContent_MakeAvailable(imgui)

# Ищем только твой Main.cpp и другие файлы строго в корне/рядом, без мусора из NDK
file(GLOB SRC_FILES "*.cpp")

add_library(mycheat SHARED ${SRC_FILES} Main.cpp)

target_include_directories(mycheat PRIVATE 
    ${imgui_SOURCE_DIR} 
)

# Подключаем стандартные библиотеки Android NDK, чтобы ушли ошибки glue.h
target_link_libraries(mycheat android log android_support)
