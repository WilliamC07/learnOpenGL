//
// Created by William Cao on 5/5/21.
//

#ifndef TESTGLFW_TEXTURE_H
#define TESTGLFW_TEXTURE_H

#include <glad/glad.h>
#include "ErrorChecker.h"

class Texture {
  private:
  unsigned int _rendererId;
  unsigned char *_localBuffer;
  // bytes per pixel
  int _width, _height, _bpp;

  public:
  Texture(const std::string &path);
  ~Texture();

  void bind(unsigned int slot = 0) const;
  void unbind() const;

  inline int getWidth() const {
    return _width;
  }
  inline int getHeight() const {
    return _height;
  }
};


#endif //TESTGLFW_TEXTURE_H
