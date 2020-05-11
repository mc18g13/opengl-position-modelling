#ifndef POSITION_HISTORY_H
#define POSITION_HISTORY_H
#include "Renderable.h"
#include <deque>
class PositionHistory : public Renderable {
public:
	PositionHistory(const std::deque<vec3> positions);

private:
	void calculateVertices(const std::deque<vec3>& positions);
	void calculateIndices();
};

#endif
