#include "VertexBuffer.h"
#include "Debug.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {

  if (data == nullptr) { std::cout << "fucked" << std::endl;}
  GLCall( glGenBuffers(1, &m_rendererID) );
  GLCall( glBindBuffer(GL_ARRAY_BUFFER, m_rendererID) );
  GLCall( glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW) );
}

VertexBuffer::~VertexBuffer() {
    GLCall( glDeleteBuffers(1, &m_rendererID) );
}

void VertexBuffer::bind() const {
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, m_rendererID) );
}

void VertexBuffer::Unbind() const {
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, 0) );
}
