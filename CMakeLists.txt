cmake_minimum_required(VERSION 3.22.1)
project(mycheat)

include(FetchContent)
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui
  GIT_TAG        v1.89
)
FetchContent_MakeAvailable(imgui)

# Собираем библиотеку из твоего кода и всех необходимых файлов ImGui
add_library(mycheat SHARED 
    main.cpp
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
)

target_include_directories(mycheat PRIVATE 
    ${imgui_SOURCE_DIR}
)

target_link_libraries(mycheat android log)
