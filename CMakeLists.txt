cmake_minimum_required(VERSION 3.16)
project(vulpine-engine VERSION 0.0.1)

# For automatic versioning accessible within source code
configure_file(VersionConfig.h.in ${CMAKE_BINARY_DIR}/generated/VersionConfig.h)
include_directories(${CMAKE_BINARY_DIR}/generated/)

# Build settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_COMPILER_LAUNCHER ccache)

set(APP_NAME "application")

file(GLOB_RECURSE VULPINE_SRC
    "src/Vulpine/*.cpp"
)

file(GLOB_RECURSE APP_SRC
    "src/Application/*.cpp")

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image)
find_package(spdlog REQUIRED)

include_directories(src libs ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
add_library(${PROJECT_NAME} STATIC ${VULPINE_SRC})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} spdlog::spdlog)
target_precompile_headers(${PROJECT_NAME} PRIVATE [["Vulpine/vppch.h"]])

add_executable(${APP_NAME} ${APP_SRC})
target_link_libraries(${APP_NAME} ${PROJECT_NAME})