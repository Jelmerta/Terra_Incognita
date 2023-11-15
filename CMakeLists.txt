cmake_minimum_required(VERSION 3.5.0)

project(
    kloenk
    VERSION 0.1.0
    LANGUAGES CXX)

add_executable(kloenk main.cpp)

target_link_libraries(kloenk PRIVATE sfml-graphics sfml-window sfml-system)
