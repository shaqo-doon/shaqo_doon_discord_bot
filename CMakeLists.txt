cmake_minimum_required (VERSION 3.6)
project(shaqo_doon)

add_executable(shaqo_doon main.cpp) 
add_subdirectory(include/sleepy-discord)

include_directories(include)

target_link_libraries(shaqo_doon sleepy-discord)