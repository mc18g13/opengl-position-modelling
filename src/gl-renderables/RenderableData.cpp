#include <RenderableData.h>

RenderableData::RenderableData(Renderable &object) :
		m_vertexBuffer(object.getVertices(), object.getTotalVertexElements() * sizeof(float)),
		m_indexBuffer(object.getIndices(), object.getIndicesSize()) {

		createVerticesForPositionAndColour();
		m_vertexArray.AddBuffer(m_vertexBuffer, m_layout);
}

void RenderableData::createVerticesForPositionAndColour() {
	m_layout.addFloat(3);
	m_layout.addFloat(3);
};

RenderableData::~RenderableData() {

}

void RenderableData::bind() const {
  m_vertexArray.bind();
  m_indexBuffer.bind();
}

unsigned int RenderableData::getIndexCount() const {
  return m_indexBuffer.getCount();
}