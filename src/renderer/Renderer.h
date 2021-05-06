//
// Created by William Cao on 5/2/21.
//

#ifndef TESTGLFW_RENDERER_H
#define TESTGLFW_RENDERER_H

#include <iostream>
#include <glad/glad.h>

#include "ErrorChecker.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer {
  private:

  public:

  void clear() const {
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
  }

  void draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader){
    ERROR_CHECKER

    shader.bind();
    va.bind();
    ib.bind();

    glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);

  }
};


#endif //TESTGLFW_RENDERER_H
