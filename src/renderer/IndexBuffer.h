//
// Created by William Cao on 5/3/21.
//

#ifndef TESTGLFW_INDEXBUFFER_H
#define TESTGLFW_INDEXBUFFER_H


/**
 * Remember that IndexBuffer should store unsigned integer types
 */
class IndexBuffer {
  private:
  unsigned int _rendererId;
  unsigned int _count;

  public:
  IndexBuffer(const unsigned int *data, unsigned int count);

  ~IndexBuffer();

  void bind() const;

  void unbind() const;

  inline unsigned int getCount() const {
    return _count;
  };
};


#endif //TESTGLFW_INDEXBUFFER_H
