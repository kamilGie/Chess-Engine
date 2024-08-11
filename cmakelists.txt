cmake_minimum_required(VERSION 3.28)

project(chess)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -std=c++20")
set(CMAKE_CXX_STANDARD 20)
file(GLOB sources "src/*.cpp" "src/*/*.cpp" "src/*/*/*.cpp" "src/*/*/*/*.cpp")

include_directories(
    ${CMAKE_SOURCE_DIR}src/resources/
)

include(FetchContent)
set(RAYLIB_VERIOSN 5.0)
FetchContent_Declare(
     raylib URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERIOSN}.tar.gz
     FIND_PACKAGE_ARGS ${RAYLIB_VERIOSN})

set(BUILD_EXAMPLES OFF CACHE  INTERNAL "")
FetchContent_MakeAvailable(raylib)

add_executable(${PROJECT_NAME} ${sources}) 


target_link_libraries(${PROJECT_NAME} raylib)

IF(APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOkit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()