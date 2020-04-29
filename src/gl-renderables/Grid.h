#ifndef GRID_H_
#define GRID_H_

#include "Renderable.h"

class Grid : public Renderable {
public:
	Grid();
	void addNumbersToIndices(std::vector<unsigned int>& data, unsigned int dataIndex, unsigned int index);
	virtual ~Grid();

    float lineSpacing = 100.0f;
    float totalWidth = 6000.0f;

    int arrayElementsForPairOfVertices = 2 * arrayElementsForOneVertex;

};

#endif
