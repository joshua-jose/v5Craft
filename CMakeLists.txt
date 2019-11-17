cmake_minimum_required(VERSION 3.6)
project(v5Craft)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17 -mcmodel=large -ggdb -DDEBUG -fPIC -Wall -Wextra -Wshadow -Wnull-dereference -Wunused-parameter -Wno-psabi -pthread -g -Os -fprofile-arcs -ftest-coverage -D THREADS_STD")

include_directories(pcbuild/V5render/)
#link_directories(pcbuild/V5render/)
add_subdirectory(pcbuild/V5render/)

include_directories(include)
link_directories("pcbuild/V5render/pcbuild" "pcbuild/V5render")


add_executable(v5Craft
	src/main.cpp
	src/Vex-Minecraft/ChunkBuilder.cpp
	src/Vex-Minecraft/TextureSheet.cpp
	src/Vex-Minecraft/block.cpp
	src/Vex-Minecraft/chunk.cpp
	src/Vex-Minecraft/cubePosition.cpp)

target_link_libraries(v5Craft V5render)
