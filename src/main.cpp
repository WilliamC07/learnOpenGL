#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE

#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "renderer/ErrorChecker.h"
#include "renderer/IndexBuffer.h"
#include "renderer/VertexBuffer.h"
#include "renderer/VertexArray.h"
#include "renderer/Shader.h"

int main(void) {
  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  // TODO: breaks on windows. START--
  //https://www.glfw.org/faq.html#41---how-do-i-create-an-opengl-30-context
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // TODO: END--

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  // TODO: doesn't work on windows
  glfwSwapInterval(1); // sync to monitor refresh rate

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLSL version " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

  float positions[] = {
    -0.5f, -0.5f,  // bottom left
    0.5f, -0.5f,   // bottom right
    0.5f, 0.5f,    // top right
    -0.5, 0.5f     // top left
  };
  // MUST BE unsigned int
  GLuint indices[] = {
    0, 1, 2,
    2, 3, 0
  };

  VertexBuffer vertexBuffer{positions, sizeof(positions)};
  VertexArray vertexArray{};
  VertexBufferLayout layout;
  layout.push<float>(2); // (x, y)
  vertexArray.addBuffer(vertexBuffer, layout);
  IndexBuffer indexBuffer{indices, 6};
  Shader shader{"resources/shaders/basic.shader"};
  shader.bind();

  vertexArray.bind();
  indexBuffer.bind();

  /* Loop until the user closes the window */
  float tick = 0;
  while (!glfwWindowShouldClose(window)) {
    ERROR_CHECKER

    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);


    // MUST BE unsigned int
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    shader.setUniform4f("u_Color", 0.8f, 0.3f, std::sin(tick), 1.0f);
    tick += .1;

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}