cmake_minimum_required (VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

project(duck_hero)

file(GLOB SOURCES 
	"*.c"
	"*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} "${SDL2_LIB}")
include_directories("${SDL2_INCLUDE_DIR}")