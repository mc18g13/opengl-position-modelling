#include <Grid.h>
#include <iostream>
#include <math.h>

namespace {
  constexpr unsigned int INDEX_X = 0;
  constexpr unsigned int INDEX_Y = 1;
  constexpr unsigned int INDEX_Z = 2;
}

Grid::Grid(float totalWidth, float lineSpacing) {
  setupVertices(totalWidth, lineSpacing);
  addNumbersToIndices(m_indices, 0, 0);
}

Grid::~Grid() {

}

void Grid::setupVertices(float totalWidth, float lineSpacing) {

  float linesPerDirection = (totalWidth / lineSpacing) + 1;

  int arrayElementsForPairOfVertices = 2 * arrayElementsForOneVertex;
  
	int vertexArrayLength = linesPerDirection * 4 * arrayElementsForPairOfVertices;
	int vertexCount = (int)((float)vertexArrayLength / (float)arrayElementsForPairOfVertices);
	setup(vertexCount, vertexCount);
	float numberOfLines = vertexCount / 2;
	float numberOfLinesInOneDirection = numberOfLines / 2;
	float extentWidth = round(numberOfLinesInOneDirection * lineSpacing / 100) * 100;
	float startPosition = 0;

//	std::cout << "numberOfVertices" << numberOfVertices << std::endl;
//	std::cout << "numberOfLines" << numberOfLines << std::endl;
//	std::cout << "numberOfLinesInOneDirection" << numberOfLinesInOneDirection << std::endl;
//	std::cout << "extentWidth" << extentWidth << std::endl;
//	std::cout << "startPosition" << startPosition << std::endl;

  float currentGridLineX = startPosition;
  float currentGridLineZ = startPosition;

  unsigned int endForX = m_vertices.size() / 2 - 1;

  for (unsigned int i = 0; i < endForX; ++i) {
		int vertexIndex = i % arrayElementsForOneVertex;
		bool isEvenIteration = i % arrayElementsForPairOfVertices >= arrayElementsForOneVertex;

    if (i % 12 == 0 && i > 0) currentGridLineX += lineSpacing;
    if (vertexIndex == INDEX_X) m_vertices.at(i) = currentGridLineX;
    if (vertexIndex == INDEX_Z) m_vertices.at(i) = isEvenIteration ? 0 : totalWidth;

    if (vertexIndex == INDEX_Y) m_vertices.at(i) = 0.0f;
		if (vertexIndex  > INDEX_Z) m_vertices.at(i) = 0.0f;
  }

  unsigned int startIndexForZ = endForX + 1; 
  for (unsigned int i = startIndexForZ; i < m_vertices.size() - 1; ++i) {
		int vertexIndex = i % arrayElementsForOneVertex;
		bool isEvenIteration = i % arrayElementsForPairOfVertices >= arrayElementsForOneVertex;

    if (i % 12 == 0 && i > startIndexForZ) currentGridLineZ += lineSpacing;
    if (vertexIndex == INDEX_X) m_vertices.at(i) = isEvenIteration ? 0 : totalWidth;
    if (vertexIndex == INDEX_Z) m_vertices.at(i) = currentGridLineZ;

    if (vertexIndex == INDEX_Y) m_vertices.at(i) = 0.0f;
		if (vertexIndex  > INDEX_Z) m_vertices.at(i) = 0.0f;
  }
}

void Grid::addNumbersToIndices(std::vector<unsigned int>& data, unsigned int dataIndex, unsigned int index) {
	bool isIndexForLinesParralelToY = index > getTotalVertexElements() / 2;
	if (index == m_vertexCount) {
		return;
	} else if (isIndexForLinesParralelToY) {
		data.at(dataIndex) = index - 1;
	} else {
    // lines parralel to x axis
		data.at(dataIndex) = index;
	}
	addNumbersToIndices(data, dataIndex + 1, index + 1);
}

