# Notes

## OpenGL notes
- [Link](http://docs.gl/)

## GLFW
- Creates window, create OpenGL context, access to input

## Drawing a triangle
- Need a vertex buffer and a shader
- Vertex buffer is just a byte array
- Vertex buffer is sent to the GPU and the shader tells the GPU what to do with the buffer
- Vertex attribute describes to the shader what the vertex buffer is
  - Ex: first 24 bytes are floats, so 6 floats in total (1 float = 4 bytes). Next 24 bytes are ints, then ...
- Shader is a GPU language
- A vertex is not a position. A vertex can include normals, position, color, etc...
  - A vertex is made up of attributes (one attribute can be position, another can be color)
  - Ex: A vertex can be: (0.5, 0.5, 0, 1.0, 0.5, 0.2, 1.0) for (x, y, z, r, g, b, a)
- Position attributes are (x, y, z) using normalized device coordinates (range: [-1, 1])

## Vertex buffer objects (VBO)
- GPU memory storage for a large number of vertices
- Perfer sending large amount of data at once than a small amount multiple times since transferring from CPU to GPU is slow

## Vertex array object (VAO)
- For storing vertex attribute
- Handles `glEnableVertexAttribArray/disable`, `glvertexAttribPointer`, and connects to VBO with `glVertexAttribPointer`

## Uniforms
- A way to get data from CPU to shaders (can also use vertex buffer)
- Set per call (set the uniform before glDraw...)
- Code:  
  Shader:
  ```
  uniform vec<1,2,3,or 4> u_<variable name>;
  ```
  CPU: (after shader program is used by calling `glUseProgram`)

## Textures
- Careful about .png transparency. You will need to enable blending and you may not see 
  the stretch depending on where the transparency is. 

## Shaders
- Mainly deal with Fragment (pixel) and vertex shaders
- Pipeline:
  - Issue draw command -> vertex shader -> fragment shader -> see on screen
- Vertex shaders:
  - Gets call for each vertex in the vertex buffer
  - Tells where to render the vertex in the screen
- Fragment shaders:
  - Runs once for each pixel that needs to get drawn (rasterize)
  - Each pixel between the sides of a triangle needs to get filled in
  - Like we have a color book with outlines of the figure. Fragment shaders fills in the space between the outline