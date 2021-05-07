//
// Created by William Cao on 5/5/21.
//

#include "Shader.h"

#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <memory>
#include <filesystem>

#include "ErrorChecker.h"


Shader::Shader(const std::string &filepath):
_rendererId{0} {
  ERROR_CHECKER
  auto[vertexShader, fragmentShader] = parseShader("resources/shaders/basic.shader");
  _rendererId = createShaders(vertexShader, fragmentShader);
}

Shader::~Shader() {
  ERROR_CHECKER
  glDeleteProgram(_rendererId);
}

void Shader::bind() const {
  ERROR_CHECKER
  glUseProgram(_rendererId);
}

void Shader::unbind() const {
  ERROR_CHECKER
  glUseProgram(0);
}

void Shader::setUniform1i(const std::string &name, int value) {
  ERROR_CHECKER
  GLint location{getUniformLocation(name)};
  glUniform1i(location, value);
}

void Shader::setUniform4f(const std::string &name, float f0, float f1, float f2, float f3) {
  ERROR_CHECKER
  GLint location{getUniformLocation(name)};
  glUniform4f(location, f0, f1, f2, f3);
}

void Shader::setUniformMat4f(const std::string &name, const glm::mat4 &mat) {
  ERROR_CHECKER
  // transpose: isRowMajor
  glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

GLint Shader::getUniformLocation(const std::string &name) {
  ERROR_CHECKER

  // check our cache for speed
  auto itr = _uniformCache.find(name);
  if(itr != _uniformCache.end()){
    return itr->second;
  }

  // TODO: should check if the uniform exists in shader to make debugging easier
  GLint location{glGetUniformLocation(_rendererId, name.c_str())};
  // want to make this a warning for debugging purposes
  // for example, if we temporarily don't use the shader with this uniform, we don't want to stop the program
  // TODO: turn into a warning
  assert(location != -1);
  _uniformCache[name] = location;
  return location;
}

GLuint Shader::compileShader(const std::string &source, GLenum type) const {
  ERROR_CHECKER

  GLuint id{glCreateShader(type)};
  const char *src = source.c_str();
  glShaderSource(id, 1, &src, NULL);
  glCompileShader(id);

  GLint result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    // error in compiling
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    std::unique_ptr<char[]> message{new char[length]};

    glGetShaderInfoLog(id, length, &length, message.get());
    std::cout << "Failed to compile shader "
              << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "\n";
    std::cout << message << "\n";
    assert(false);
  }

  return id;
}

/**
 * Create a shader program
 * @param vertexShader Source code for vertex shader
 * @param fragmentShader Source code for fragment shader
 * @return
 */
GLuint Shader::createShaders(const std::string &vertexShader, const std::string &fragmentShader) const {
  ERROR_CHECKER

  GLuint program{glCreateProgram()};
  GLuint vs{compileShader(vertexShader, GL_VERTEX_SHADER)};
  GLuint fs{compileShader(fragmentShader, GL_FRAGMENT_SHADER)};

  // link the shaders to the "program"
  // like joining the .o program to main.cpp
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  // shaders are now part of "program"
  glLinkProgram(program);
  glValidateProgram(program);
  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) {
    int length;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
    std::unique_ptr<char[]> message{new char[length]};
    glGetProgramInfoLog(program, length, NULL, message.get());
    std::cout << "Failed linking shaders:\n"
              << message << "\n";
    assert(false);
  }

  // like deleting the .o files when compiling c code
  glDeleteShader(vs);
  glDeleteShader(fs);

  // technically should run glDeleteShader
  return program;
}

/**
 * Returns [vertex shader, fragment shader]
 * @param filepath
 * @return
 */
std::pair<std::string, std::string> Shader::parseShader(const std::string &filepath) const {
  // TODO: should store uniforms and their types for debugging
  auto cwd = std::filesystem::current_path().string();
  std::cout << "Reading shaders from: " << cwd << '/' << filepath << "\n";
  std::ifstream stream{filepath};

  if (!stream) {
    std::cout << "Error: Could not open " << filepath << "\n";
    assert(false);
  }

  enum class ShaderType {
    NONE = -1,
    VERTEX = 0,
    FRAGMENT = 1
  };
  ShaderType type{ShaderType::NONE};
  std::string line;
  std::stringstream ss[2];
  while (std::getline(stream, line)) {
    if (line.find("#shader") != std::string::npos) {
      if (line.find("vertex") != std::string::npos) {
        type = ShaderType::VERTEX;
      } else if (line.find("fragment") != std::string::npos) {
        type = ShaderType::FRAGMENT;
      } else {
        assert(false);
      }
    } else {
      assert(type != ShaderType::NONE);
      ss[(int) type] << line << '\n';
    }
  }

  return {ss[0].str(), ss[1].str()};
}

