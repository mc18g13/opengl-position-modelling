#ifndef RENDERABLEDATA_H_
#define RENDERABLEDATA_H_

#include "Renderable.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class RenderableData {
private:
  VertexArray        m_vertexArray;
  VertexBuffer       m_vertexBuffer;
  IndexBuffer        m_indexBuffer;
  VertexBufferLayout m_layout;

public:
  RenderableData(Renderable &object);
  virtual ~RenderableData();
  void bind() const;
  unsigned int getIndexCount() const;
private:
	void createVerticesForPositionAndColour();
};

#endif /* SRC_GL_RENDERABLES_RENDERABLEDATA_H_ */
