#ifndef GRID_H_
#define GRID_H_

#include "Renderable.h"

class Grid : public Renderable {
public:
	Grid(float totalWidth = 1000.0f, float lineSpacing = 100.0f);
	virtual ~Grid();
  
private:
	void addNumbersToIndices(std::vector<unsigned int>& data, unsigned int dataIndex, unsigned int index);
  void setupVertices(float totalWidth, float lineSpacing);
};

#endif
