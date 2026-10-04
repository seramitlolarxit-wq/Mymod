cmake_minimum_required(VERSION 3.18)
project(Rocket)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(rocket SHARED
    main.cpp
)

target_include_directories(rocket PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends
)

# Раскомментируй, когда положишь исходники ImGui в папку imgui/
# target_sources(rocket PRIVATE
#     imgui/imgui.cpp
#     imgui/imgui_draw.cpp
#     imgui/imgui_widgets.cpp
#     imgui/imgui_tables.cpp
#     imgui/backends/imgui_impl_opengl3.cpp
# )

find_library(log-lib log)
find_library(android-lib android)
find_library(EGL-lib EGL)
find_library(GLES-lib GLESv3)
find_library(dl-lib dl)

target_link_libraries(rocket
    ${log-lib}
    ${android-lib}
    ${EGL-lib}
    ${GLES-lib}
    ${dl-lib}
)
