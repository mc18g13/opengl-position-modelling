#include "Renderable.h"
#include <iostream>

namespace {
  const int COUNT_OF_VALUES_IN_RENDERABLE_POINT = 6;
}

Renderable::Renderable() {

}

Renderable::~Renderable() {

}

void Renderable::setup(
  unsigned int vertexCount,
  unsigned int indexArraySize) {

	m_vertexCount = vertexCount;
	createVertexArray(vertexCount);
	createIndexArray(indexArraySize);
}

void Renderable::createVertexArray(unsigned int size) {
	m_vertices = std::vector<float>(size * COUNT_OF_VALUES_IN_RENDERABLE_POINT, 0.0);
}

void Renderable::createIndexArray(unsigned int size) {
	m_totalVertexElements = size * COUNT_OF_VALUES_IN_RENDERABLE_POINT;
	m_indices = std::vector<unsigned int>(size, 0);
}

unsigned int Renderable::getVertexCount() {
	return m_vertexCount;
}

float* Renderable::getVertices() {
	return m_vertices.data();
}

unsigned int* Renderable::getIndices() {
	return m_indices.data();
}

unsigned int Renderable::getTotalVertexElements() {
	return m_totalVertexElements;
}

unsigned int Renderable::getIndicesSize() {
	return m_indices.size();
}

void Renderable::printVertices() const {
  std::cout << std::endl;
	for (unsigned int i = 0; i < m_vertices.size(); ++i) {
		int vertexIndex = i % arrayElementsForOneVertex;
		if (vertexIndex < 3) {
			std::cout << m_vertices.at(i) << " ";
		} else if (vertexIndex == 3) {
			std::cout << std::endl;
		}
	}
  std::cout << std::endl;
}

void Renderable::printIndices() const {
  std::cout << std::endl;
  std::cout << "size " << m_indices.size() << std::endl;
	for (unsigned int i = 0; i < m_indices.size(); ++i) {
		std::cout << m_indices.at(i) << std::endl;
	}
  std::cout << std::endl;
}

Renderable::Renderable(const Renderable &newRenderable) {
  this->m_vertices            = newRenderable.m_vertices;
	this->m_indices             = newRenderable.m_indices;
	this->m_vertexCount         = newRenderable.m_vertexCount;
	this->m_totalVertexElements = newRenderable.m_totalVertexElements;
}


Renderable Renderable::operator+(const Renderable& additionalRenderable) {
  Renderable jointRenderable;
  unsigned int jointRenderableVertexCount = this->m_vertexCount    + additionalRenderable.m_vertexCount;    
  unsigned int jointRenderableIndicesSize = this->m_indices.size() + additionalRenderable.m_indices.size();
  
  jointRenderable.setup(
    jointRenderableVertexCount, 
    jointRenderableIndicesSize);

  std::copy(
    this->m_vertices.begin(), this->m_vertices.end(), 
    jointRenderable.m_vertices.begin());
  std::copy(
    additionalRenderable.m_vertices.begin(), additionalRenderable.m_vertices.end(), 
    jointRenderable.m_vertices.begin() + this->m_vertices.size());

  std::copy(
    this->m_indices.begin(), this->m_indices.end(), 
    jointRenderable.m_indices.begin());
  std::copy(
    additionalRenderable.m_indices.begin(), additionalRenderable.m_indices.end(), 
    jointRenderable.m_indices.begin() + this->m_indices.size());
  
  for (int i = this->m_indices.size(); i < jointRenderable.m_indices.size(); ++i) {
    jointRenderable.m_indices.at(i) += this->m_vertexCount;
  }

  return jointRenderable;
}

Renderable Renderable::operator+=(const Renderable& additionalRenderable) {
  *this = *this + additionalRenderable;
  return *this;
}