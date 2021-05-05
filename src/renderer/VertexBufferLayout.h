//
// Created by William Cao on 5/4/21.
//

#ifndef TESTGLFW_VERTEXBUFFERLAYOUT_H
#define TESTGLFW_VERTEXBUFFERLAYOUT_H

#include <vector>
#include <glad/glad.h>

/**
 * Vertices are made up of elements.
 */
struct VertexBufferElement {
  GLenum type;
  unsigned int count;
  GLboolean needsToBeNormalized;
  unsigned int offset;
};

/**
 * Position of an element is the "offset"
 * Size of an vertex is the "stride"
 */
class VertexBufferLayout {
  private:
  std::vector<VertexBufferElement> _elements;
  unsigned int _stride;
  unsigned int _offset;

  public:
  VertexBufferLayout() : _stride{0}, _offset{0} {}

  template<typename T>
  void push(unsigned int count) {
    // not implemented
    assert(false);
  }

  template<>
  void push<float>(unsigned int count) {
    _elements.push_back({GL_FLOAT, count, GL_FALSE, _offset});
    _stride += count * sizeof(GLfloat);
    _offset += count * sizeof(GLfloat);
  }

  template<>
  void push<unsigned int>(unsigned int count) {
    // TODO: Not sure why the video (buffer layout abstraction 19:32) puts "needsToBeNormalized" to false
    _elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE, _offset});
    _stride += count * sizeof(GLuint);
    _offset += count * sizeof(GLuint);
  }

  template<>
  void push<unsigned char>(unsigned int count) {
    _elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE, _offset});
    _stride += count * sizeof(GLubyte);
    _offset += count * sizeof(GLubyte);
  }

  const std::vector<VertexBufferElement> &getElements() const {
    return _elements;
  }

  unsigned int getStride() const {
    return _stride;
  }
};


#endif //TESTGLFW_VERTEXBUFFERLAYOUT_H
