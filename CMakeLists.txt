cmake_minimum_required(VERSION 3.16)
project(vulpine-engine VERSION 0.0.1)

# For automatic versioning accessible within source code
configure_file(VersionConfig.h.in ${CMAKE_BINARY_DIR}/generated/VersionConfig.h)
include_directories(${CMAKE_BINARY_DIR}/generated/)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB_RECURSE SRC
    "src/*.cpp"
)

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image)
find_package(spdlog REQUIRED)

include_directories(src libs ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} spdlog::spdlog)
target_precompile_headers(${PROJECT_NAME} PRIVATE [["Vulpine/vppch.h"]])