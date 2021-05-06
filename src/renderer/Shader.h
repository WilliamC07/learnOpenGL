//
// Created by William Cao on 5/5/21.
//

#ifndef TESTGLFW_SHADER_H
#define TESTGLFW_SHADER_H

#include <glad/glad.h>
#include <string>
#include <utility>
#include <unordered_map>

class Shader {
  private:
  unsigned int _rendererId;
  std::unordered_map<std::string, GLint> _uniformCache;

  public:
  Shader(const std::string &filepath);
  ~Shader();

  void bind() const;
  void unbind() const;

  void setUniform1i(const std::string &name, int value);
  void setUniform4f(const std::string &name, float f0, float f1, float f2, float f3);

  private:
  GLint getUniformLocation(const std::string &name);
  GLuint compileShader(const std::string &source, GLenum type) const;
  GLuint createShaders(const std::string &vertexShader, const std::string &fragmentShader) const;
  std::pair<std::string, std::string> parseShader(const std::string &filepath) const;
};


#endif //TESTGLFW_SHADER_H
