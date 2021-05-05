//
// Created by William Cao on 5/3/21.
//

#include "VertexBuffer.h"
#include <glad/glad.h>

#include "ErrorChecker.h"

VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
  ERROR_CHECKER

  glGenBuffers(1, &_rendererId);
  glBindBuffer(GL_ARRAY_BUFFER, _rendererId);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
  ERROR_CHECKER
  glDeleteBuffers(1, &_rendererId);
}

void VertexBuffer::bind() const {
  ERROR_CHECKER
  glBindBuffer(GL_ARRAY_BUFFER, _rendererId);
}

void VertexBuffer::unbind() const {
  ERROR_CHECKER
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
