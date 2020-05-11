#include <PositionHistory.h>
#include <iostream>

PositionHistory::PositionHistory(const std::deque<vec3> positions) {
	unsigned int vertexCount = positions.size();
	unsigned int indexCount  =  2 * vertexCount;
	setup(vertexCount, indexCount);

	calculateVertices(positions);
	calculateIndices();
}


void PositionHistory::calculateVertices(
  const std::deque<vec3>& positions) {

  for (unsigned int i = 0; i < positions.size(); ++i) {
    int j = i * 6;

    m_vertices.at(j)     = positions.at(i).x;
    m_vertices.at(j + 1) = positions.at(i).y;
    m_vertices.at(j + 2) = positions.at(i).z;
    m_vertices.at(j + 3) = 0;
    m_vertices.at(j + 4) = 0;
    m_vertices.at(j + 5) = 0;
	}
}

void PositionHistory::calculateIndices() {
	for (unsigned int i = 1; i < getIndicesSize(); ++i) {
    // bool isEven = i % 2 == 0;
    // if (isEven) {
    //   m_indices.at(i) = i / 2;
    // } else {
    //   m_indices.at(i) = (i - 1) / 2;
    // }
    // m_indices.at(i) = i;
	}
}
