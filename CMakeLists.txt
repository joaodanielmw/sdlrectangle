cmake_minimum_required(VERSION 3.21)
project(sdl_rectangle LANGUAGES C)

find_package(SDL3 REQUIRED CONFIG)

add_executable(
	sdl_rectangle
	src/main.c
)

target_include_directories(sdl_rectangle PRIVATE include)
target_link_libraries(sdl_rectangle PRIVATE SDL3::SDL3)
