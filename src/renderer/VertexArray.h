//
// Created by William Cao on 5/3/21.
//

#ifndef TESTGLFW_VERTEXARRAY_H
#define TESTGLFW_VERTEXARRAY_H

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

/**
 * VAO
 *
 * For storing attributes tied to a VBO (Vertex buffer object). See addBuffer().
 */
class VertexArray {
  private:
  unsigned int _rendererId;

  public:
  VertexArray();

  ~VertexArray();

  void addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) const;

  void bind() const;

  void unbind() const;
};


#endif //TESTGLFW_VERTEXARRAY_H
