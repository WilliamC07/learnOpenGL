//
// Created by William Cao on 5/3/21.
//

#include "IndexBuffer.h"
#include <glad/glad.h>

#include "ErrorChecker.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) :
  _count{count} {
  ERROR_CHECKER
  assert(sizeof(unsigned int) == sizeof(GLuint));

  glGenBuffers(1, &_rendererId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);

  // vertex buffer object (VAO) must exist (https://www.khronos.org/opengl/wiki/Vertex_Specification#Index_buffers)
  // On MacOS, no check error is notified in glGetError(). Not sure on other platform, so we have to include this check
  // TODO: Add debug preprocessor guard
  GLint currentBindedVertexArray;
  glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentBindedVertexArray);
  assert(currentBindedVertexArray != 0);
}

IndexBuffer::~IndexBuffer() {
  ERROR_CHECKER
  glDeleteBuffers(1, &_rendererId);
}

void IndexBuffer::bind() const {
  ERROR_CHECKER
  glBindBuffer(GL_ARRAY_BUFFER, _rendererId);
}

void IndexBuffer::unbind() const {
  ERROR_CHECKER
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}