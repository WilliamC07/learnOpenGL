#define GL_SILENCE_DEPRECATION
#include <string>
#include <iostream>
#include <cassert>
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>

static GLuint compileShader(const std::string &source, GLenum type){
  GLuint id{glCreateShader(type)};
  const char *src = source.c_str();
  glShaderSource(id, 1, &src, NULL);
  glCompileShader(id);

  GLint result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if(result == GL_FALSE){
    // error in compiling
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    // TODO: unique pointer learning?
    char *message = new char[length];
    glGetShaderInfoLog(id, length, &length, message);
    std::cout << "Failed to compile shader "
              << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "\n";
    std::cout << message << "\n";
    delete[] message;
    return 0;
  }

  return id;
}

/**
 * Create a shader program
 * @param vertexShader Source code for vertex shader
 * @param fragmentShader Source code for fragment shader
 * @return
 */
static GLuint createShaders(const std::string &vertexShader, const std::string &fragmentShader){
  GLuint program{glCreateProgram()};
  GLuint vs{compileShader(vertexShader, GL_VERTEX_SHADER)};
  GLuint fs{compileShader(fragmentShader, GL_FRAGMENT_SHADER)};

  assert(vs);
  assert(fs);

  // link the shaders to the "program"
  // like joining the .o program to main.cpp
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  // shaders are now part of "program"
  glLinkProgram(program);
  glValidateProgram(program);
  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if(status == GL_FALSE){
    int length;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
    char *message = new char[length];
    glGetProgramInfoLog(program, length, NULL, message);
    std::cout << "Failed linking shaders:\n"
              << message << "\n";
  }

  // like deleting the .o files when compiling c code
  glDeleteShader(vs);
  glDeleteShader(fs);

  // technically should run glDeleteShader
  return program;
}

int main(void) {
  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  //https://www.glfw.org/faq.html#41---how-do-i-create-an-opengl-30-context
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  float positions[6] = {
    -0.5f, -0.5f, // this is 1st vertex
    0.0f, 0.5f, // this is the 2nd vertex
    0.5f, -0.5f // this is the 3rd vertex
  };
  GLuint VBO;  // id of the buffer
  glGenBuffers(1, &VBO);  // creates a buffer, stores the ID in "buffer"
  // OpenGL will use the buffer that is currently binded
  glBindBuffer(GL_ARRAY_BUFFER, VBO);  // create an array buffer (byte array)
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

  // must have this if we use attribute
  glEnableVertexAttribArray(0); // 0 is the index of attribute storing position
  // do this for each attribute of the vertex
  // in this case we just have 1 attribute
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

  std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLSL version " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

  std::string vertexShader = R"(
  #version 330 core
  layout(location = 0) in vec2 position;
  void main(){
    gl_Position = vec4(position, 0.0, 1.0);
  }
  )";
  std::string fragmentShader = R"(
  #version 330 core
  out vec4 FragColor;
  void main(){
    FragColor = vec4(1.0, 0.5, 0.2, 1.0);
  }
  )";
  GLuint shader = createShaders(vertexShader, fragmentShader);
  glUseProgram(shader);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}