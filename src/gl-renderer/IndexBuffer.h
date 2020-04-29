#pragma once

class IndexBuffer
{
private:
  unsigned int m_RendererID;
  unsigned int m_Count;

public:
  IndexBuffer();
  IndexBuffer(const unsigned int* indices, unsigned int count);
  ~IndexBuffer();

  void bind() const;
  void Unbind() const;

  inline unsigned int getCount() const { return m_Count; }
};
