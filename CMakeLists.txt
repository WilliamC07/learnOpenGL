cmake_minimum_required(VERSION 3.17)

project(testglfw)

set(CMAKE_CXX_STANDARD 20)

add_executable(testglfw
        main.cpp)

add_subdirectory(vendor/glad)

# https://www.glfw.org/docs/latest/build_guide.html#build_link_cmake_source
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/glfw)

target_link_libraries(testglfw glad glfw)
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})