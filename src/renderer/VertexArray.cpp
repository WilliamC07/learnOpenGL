//
// Created by William Cao on 5/3/21.
//

#include "VertexArray.h"
#include "ErrorChecker.h"

VertexArray::VertexArray() {
  ERROR_CHECKER
  glGenVertexArrays(1, &_rendererId);
}

VertexArray::~VertexArray() {
  ERROR_CHECKER
  glDeleteVertexArrays(1, &_rendererId);
}

void VertexArray::addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) const {
  ERROR_CHECKER

  this->bind();
  vb.bind();
  const auto &elements = layout.getElements();
  for (unsigned int i = 0; i < elements.size(); i++) {
    const auto &element = elements[i];
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, element.count, element.type, element.needsToBeNormalized,
                          layout.getStride(), (void *) element.offset);
  }
}

void VertexArray::bind() const {
  ERROR_CHECKER
  glBindVertexArray(_rendererId);
}

void VertexArray::unbind() const {
  ERROR_CHECKER
  glBindVertexArray(0);
}
