cmake_minimum_required(VERSION 3.10.0)
project(CNet VERSION 0.1.0 LANGUAGES C)

add_executable(CNet)

target_include_directories(CNet PUBLIC include)
file(GLOB SRC src/*.c)
target_sources(CNet PUBLIC ${SRC})