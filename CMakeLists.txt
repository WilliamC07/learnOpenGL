cmake_minimum_required(VERSION 3.17)

project(testglfw)

set(CMAKE_CXX_STANDARD 20)

add_executable(testglfw
        main.cpp)

add_subdirectory(vendor/glad)

add_subdirectory(vendor/glfw)
include_directories(vendor/glfw/include)
target_link_libraries(testglfw glad glfw ${GLFW_LIBRARIES})

file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})