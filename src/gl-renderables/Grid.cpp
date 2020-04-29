#include <Grid.h>
#include <iostream>
#include <math.h>

Grid::Grid() {
  setupVertices();
  addNumbersToIndices(m_indices, 0, 0);
}

Grid::~Grid() {

}

void Grid::setupVertices() {
  float lineSpacing = 100.0f;
  float totalWidth = 10000.0f;

  int arrayElementsForPairOfVertices = 2 * arrayElementsForOneVertex;
  
	int vertexArrayLength = 6000;
	int vertexCount = (int)((float)vertexArrayLength / (float)arrayElementsForOneVertex);
	setup(vertexCount, vertexCount);
	float numberOfLines = vertexCount / 2;
	float numberOfLinesInOneDirection = numberOfLines / 2;
	float extentWidth = round(numberOfLinesInOneDirection * lineSpacing / 100) * 100;
	float startPosition = -extentWidth / 2;

//	std::cout << "numberOfVertices" << numberOfVertices << std::endl;
//	std::cout << "numberOfLines" << numberOfLines << std::endl;
//	std::cout << "numberOfLinesInOneDirection" << numberOfLinesInOneDirection << std::endl;
//	std::cout << "extentWidth" << extentWidth << std::endl;
//	std::cout << "startPosition" << startPosition << std::endl;

  float currentGridLineX = startPosition;
  float currentGridLineZ = startPosition;

	for (unsigned int i = 0; i < m_vertices.size(); i++) {

		int vertexIndex = i % arrayElementsForOneVertex;
		bool isEvenIteration = i % arrayElementsForPairOfVertices >= arrayElementsForOneVertex;

		if (i <= m_vertices.size() / 2) {

			if (i % 12 == 0) currentGridLineX += lineSpacing;
			if (vertexIndex == 0) m_vertices.at(i) = currentGridLineX;
			if (vertexIndex == 2) m_vertices.at(i) = isEvenIteration ? -totalWidth : totalWidth;

		} else {

			if (i % 12 == 0) currentGridLineZ += lineSpacing;
			if (vertexIndex == 0) m_vertices.at(i) = isEvenIteration ? -totalWidth : totalWidth;
			if (vertexIndex == 2) m_vertices.at(i) = currentGridLineZ;

		}

		if (vertexIndex == 1) m_vertices.at(i) = 0.0f;
		if (vertexIndex  > 2) m_vertices.at(i) = 0.0f;

	}
}

void Grid::addNumbersToIndices(std::vector<unsigned int>& data, unsigned int dataIndex, unsigned int index) {
	bool isIndexForLinesParralelToZ = index > getTotalVertexElements() / 2;
	if (index == m_vertexCount) {
		return;
	} else if (isIndexForLinesParralelToZ) {
		data.at(dataIndex) = index - 1;
	} else {
    // lines parralel to x axis
		data.at(dataIndex) = index;
	}
	addNumbersToIndices(data, dataIndex + 1, index + 1);
}

