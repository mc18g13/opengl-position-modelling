#ifndef GRID_H_
#define GRID_H_

#include "Renderable.h"

class Grid : public Renderable {
public:
	Grid();
	virtual ~Grid();
  
private:
	void addNumbersToIndices(std::vector<unsigned int>& data, unsigned int dataIndex, unsigned int index);
  void setupVertices();
};

#endif
