//
// Created by William Cao on 5/3/21.
//

#ifndef TESTGLFW_VERTEXBUFFER_H
#define TESTGLFW_VERTEXBUFFER_H

#include <cassert>

class VertexBuffer {
  private:
  unsigned int _rendererId;

  public:
  VertexBuffer(const void *data, unsigned int size);

  ~VertexBuffer();

  void bind() const;

  void unbind() const;

};


#endif //TESTGLFW_VERTEXBUFFER_H
