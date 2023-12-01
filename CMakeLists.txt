cmake_minimum_required(VERSION 3.27)

project(
    kloenk
    VERSION 0.1.0
    LANGUAGES CXX C)

add_executable(kloenk src/main.cpp src/shader_m.h ${TARGET_H})
target_include_directories(kloenk PUBLIC include)

add_subdirectory(glad/)
target_link_libraries(kloenk PRIVATE glfw glad)

# When we build for web, we use emscripten to generate WASM/JS/HTML files.
if (EMSCRIPTEN)
    message(STATUS "emscripten environment is loaded")
    # Add Emscripten-specific link options
    target_link_options(kloenk PRIVATE
        -sUSE_GLFW=3 # Use Emscripten-provided GLFW
        -sMAX_WEBGL_VERSION=2 # Defaults to WebGL 2.0 implementation, but allows backwards compatibility
    )
    set_target_properties(kloenk 
        PROPERTIES SUFFIX ".html")
else()
    message(STATUS "emscripten environment is NOT loaded (local build)")
endif()

# Optimise the build (both for debug and release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O3")

# When including GLFW as part of your build, you probably don't want to build the GLFW tests, examples and documentation. To disable these, set the corresponding cache variables before adding the GLFW source tree.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Extra warnings that will hopefully help debugging
target_compile_options(kloenk PRIVATE -Wall -Wextra)

