#ifndef CYLINDER_H
#define CYLINDER_H
#include <Renderable.h>

class Cylinder : public Renderable {
public:
	Cylinder(vec3 unitVectorDirectionOfCylinder, vec3 startPointCoordinate, vec3 color, float length, float radius);

private:
	void calculateVertices(vec3 unitVectorDirectionOfCylinder, vec3 startPointCoordinate, vec3 color, float length, float radius);
	void calculateIndices();
};

#endif
