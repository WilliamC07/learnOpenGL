//
// Created by William Cao on 5/5/21.
//

#include "Texture.h"

#include <filesystem>

#include "../vendor/stb_image/stb_image.h"

Texture::Texture(const std::string &path) :
  _rendererId{0}, _localBuffer{nullptr}, _width{0}, _height{0}, _bpp{0} {
  ERROR_CHECKER
  auto cwd = std::filesystem::current_path().string();
  std::cout << "Reading image from: " << cwd << '/' << path << '\n';

  // openGL: bottom gl is (0, 0), but jpeg
  stbi_set_flip_vertically_on_load(true);
  // rgba = 4
  _localBuffer = stbi_load(path.c_str(), &_width, &_height, &_bpp, 4);

  if(!_localBuffer){
    std::cout << "Error loading texture from disk: \n"
              << stbi_failure_reason() << std::endl;
    assert(false);
  }

  glGenTextures(1, &_rendererId);
  glBindTexture(GL_TEXTURE_2D, _rendererId);

  // required 4 parameters for textures
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

  // give our texture image to GL
  // jpeg is 8 bits per pixel
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _localBuffer);
  glBindTexture(GL_TEXTURE_2D, 0);

  stbi_image_free(_localBuffer);
}

Texture::~Texture() {
  ERROR_CHECKER

  glDeleteTextures(1, &_rendererId);
}

void Texture::bind(unsigned int slot) const {
  ERROR_CHECKER
  // there is a upper limit to texture slots
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, _rendererId);
}

void Texture::unbind() const {

}
