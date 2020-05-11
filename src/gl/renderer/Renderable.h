
#ifndef RENDERABLE_H_
#define RENDERABLE_H_

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "GLMathematics.h"

#include <algorithm>
#include <vector>

class Renderable : public GLMathematics {
protected:
	static const unsigned arrayElementsForOneVertex = 6;
	std::vector<float>        m_vertices;
	std::vector<unsigned int> m_indices;
	unsigned int  m_vertexCount;
	unsigned int  m_totalVertexElements;

	void createVertexArray(unsigned int size);
	void createIndexArray(unsigned int size);

  void createVerticesForPositionAndColour();

public:
  Renderable();
	virtual ~Renderable();

	void setup(unsigned int vertexCount,
             unsigned int indexArraySize);

	float* getVertices();
	unsigned int* getIndices();

	unsigned int getVertexCount();
	unsigned int getTotalVertexElements();
  unsigned int getIndicesSize();

	void printVertices() const;
	void printIndices() const;

  Renderable(const Renderable &newRenderable);
  Renderable operator=(const Renderable& additionalRenderable);
  Renderable operator+(const Renderable& additionalRenderable);
  Renderable operator+=(const Renderable& additionalRenderable);
};

#endif
