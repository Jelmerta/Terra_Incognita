cmake_minimum_required(VERSION 3.5)

project(
    kloenk
    VERSION 0.1.0
    LANGUAGES CXX C)

add_executable(kloenk src/main.cpp)

add_subdirectory(glad/)

target_link_libraries(kloenk PRIVATE glfw GL glad)

if (EMSCRIPTEN)
    # Add Emscripten-specific link options
    target_link_options(kloenk PRIVATE
        -sUSE_GLFW=3 # Use Emscripten-provided GLFW
    )
endif()