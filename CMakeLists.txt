cmake_minimum_required (VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

if(CMAKE_CXX_COMPILER MATCHES "MSVC")
	set(CMAKE_CXX_FLAGS "/EHsc /Zi")
	set(CMAKE_SHARED_LINKER_FLAGS "/DEBUG /OPT:REF /OPT:ICF")
	set(CMAKE_CREATE_WIN32_EXE "/SUBSYSTEM:WINDOWS")
endif()

project(duck_hero)

file(GLOB SOURCES 
	"*.c"
	"*.cpp"
	"external/*.c"
	"external/*.cpp"
)

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} "${SDL2_LIBRARY}" "${SDL2MAIN_LIBRARY}")
include_directories("${SDL2_INCLUDE_DIR}")

find_package(SDL2_gfx REQUIRED)
target_link_libraries(${PROJECT_NAME} "${SDL2_GFX_LIBRARY}")
include_directories("${SDL2_GFX_INCLUDE_DIR}")

find_package(SDL2_image REQUIRED)
target_link_libraries(${PROJECT_NAME} "${SDL2_IMAGE_LIBRARY}")
include_directories("${SDL2_IMAGE_INCLUDE_DIR}")

find_package(SDL2_mixer REQUIRED)
target_link_libraries(${PROJECT_NAME} "${SDL2_MIXER_LIBRARY}")
include_directories("${SDL2_MIXER_INCLUDE_DIR}")

find_package(SDL2_ttf REQUIRED)
target_link_libraries(${PROJECT_NAME} "${SDL2_TTF_LIBRARY}")
include_directories("${SDL2_TTF_INCLUDE_DIR}")

find_package(PhysFS REQUIRED)
target_link_libraries(${PROJECT_NAME} "${PHYSFS_LIBRARY}")
include_directories("${PHYSFS_INCLUDE_DIR}")