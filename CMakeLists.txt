cmake_minimum_required(VERSION 3.17)

project(testglfw)

set(CMAKE_CXX_STANDARD 20)

add_executable(testglfw
        src/main.cpp src/renderer/Renderer.cpp src/renderer/Renderer.h
        src/renderer/ErrorChecker.h src/renderer/VertexBuffer.cpp
        src/renderer/VertexBuffer.h src/renderer/IndexBuffer.cpp
        src/renderer/IndexBuffer.h src/renderer/VertexArray.cpp
        src/renderer/VertexArray.h src/renderer/VertexBufferLayout.h
        src/renderer/Shader.cpp src/renderer/Shader.h
        src/renderer/Texture.cpp src/renderer/Texture.h
        src/vendor/stb_image/stb_image.h src/vendor/stb_image/std_image.cpp
        src/vendor/imgui/imconfig.h
        src/vendor/imgui/imgui.cpp
        src/vendor/imgui/imgui.h
        src/vendor/imgui/imgui_demo.cpp
        src/vendor/imgui/imgui_draw.cpp
        src/vendor/imgui/imgui_impl_glfw.cpp
        src/vendor/imgui/imgui_impl_glfw.h
        src/vendor/imgui/imgui_impl_opengl3.cpp
        src/vendor/imgui/imgui_impl_opengl3.h
        src/vendor/imgui/imgui_internal.h
        src/vendor/imgui/imgui_tables.cpp
        src/vendor/imgui/imgui_widgets.cpp
        src/vendor/imgui/imstb_rectpack.h
        src/vendor/imgui/imstb_textedit.h
        src/vendor/imgui/imstb_truetype.h)

add_subdirectory(vendor/glad)

# https://www.glfw.org/docs/latest/build_guide.html#build_link_cmake_source
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/glfw)

add_subdirectory(vendor/glm)

# https://www.glfw.org/docs/3.0/build.html#build_link_cmake_source
# May need to add GLU (add ${OPENGL_glu_LIBRARY})
target_link_libraries(testglfw glad glfw ${GLFW_LIBRARIES} glm)
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})