cmake_minimum_required(VERSION 3.17)

project(testglfw)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework OpenGl")

add_executable(testglfw
        main.cpp)

add_subdirectory(vendor/glfw)
include_directories(vendor/glfw/include)
target_link_libraries(testglfw glfw ${GLFW_LIBRARIES})