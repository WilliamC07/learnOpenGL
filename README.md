# Adding libraries to cpp using cmake

1. Create a vendor folder and change directory into it. This will hold all the libraries.
    ```shell
    mkdir vendor && cd vendor
    ```
1. Add the submodule of the library. In this example, we are using glfw
    ```shell
   git submodule add https://github.com/glfw/glfw.git 
   ```
1. In ```CMakeLists.txt```, add the following at the end of the file:
   ```
   add_subdirectory(vendor/glfw)
   include_directories(vendor/glfw/include)
   target_link_libraries(<app name> glfw ${GLFW_LIBRARIES}) 
   
   # I had to add this complier flag (somewhere in top of file) in macOS
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework OpenGl")
   ```
1. When you clone the project from github, make sure you clone by:
   ```shell
   git clone *link*
   # If already cloned, start here
   git submodule update --init --recursive # inside cloned repo dir
   ```
   
## Adding 3rd party library using cmake
1. Create another directory in the root of the project (`vendor` in this project)
2. Add the libraries there.
3. If the libraries have a `CMakeLists.txt`, everything is good. If it doesn't, one needs to be created. See `vendor/glad/CmakeLists.txt` for an example on how to create one.
4. In the root project CMakeLists.txt, add `add_subdirectory(vendor/<library dir name>)` for each library. Then add `target_link_libraries(<project name> <library> <and another library>)`.

## Run cmake
1. Create a build directory and change directory into it:  
   `mkdir build && cd build`
2. Run cmake  
   `cmake ..`
3. Run make  
   `make`
4. Run the executable  
   `./testglfw`
   
## Cross platform code generation for OpenGL
- [GLAD](https://gen.glad.sh/)
- Make sure you choose "Version 4.1" for "gl" and "core". Add all the extensions. Then generate.
- Generated files go into `vendor/glad`
- Ordering matters for `#include` and initializing GLAD

# Sources:
- https://www.glfw.org/docs/3.0/build.html#build_link_cmake_source
- https://stackoverflow.com/questions/23450334/opengl-3-3-4-1-on-mac-osx-10-9-using-glfw-library
- https://www.youtube.com/watch?v=OR4fNpBjmq8&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=2