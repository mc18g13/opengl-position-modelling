#include <Cylinder.h>
#include <math.h>
#include <iostream>

Cylinder::Cylinder(vec3 unitVectorDirectionOfCylinder, vec3 startPointCoordinate, vec3 color, float length, float radius) {
	unsigned int vertexCount = 20;
  const unsigned int INDICES_FOR_EACH_VERTEX = 3;
	unsigned int indexCount = INDICES_FOR_EACH_VERTEX * vertexCount;
	setup(vertexCount, indexCount);

	calculateVertices(unitVectorDirectionOfCylinder, startPointCoordinate, color, length, radius);
	calculateIndices();
}


void Cylinder::calculateVertices(
  vec3 unitVectorDirectionOfCylinder, vec3 startPointCoordinate, vec3 color,
  float length, float radius) {

	float currentAngle = 0.0f;
	unsigned int iterationsForPairsOfVertices = (m_vertexCount / 2);

	vec3 centreLineOfCylinder(0.0f, 0.0f, 1.0f);
	quat rotationToUpdateDirection = RotationBetweenVectors(unitVectorDirectionOfCylinder, centreLineOfCylinder);

	float angle = 2 * M_PI / (float)(iterationsForPairsOfVertices - 1);
	for (unsigned int i = 0; i < iterationsForPairsOfVertices; i++) {
		int j = i * 12;

    float x = cos(currentAngle) * radius;
    float y = sin(currentAngle) * radius;

    quat unmappedCoordinateClose = quat(0.0f, x, y, 0.0f);
    quat unmappedCoordinateFar   = quat(0.0f, x, y, length);
    
    quat inverseQuaternionToReverseDirectionChange = inverse(rotationToUpdateDirection);
    quat remappedCoordinateClose = inverseQuaternionToReverseDirectionChange * unmappedCoordinateClose * rotationToUpdateDirection;
    quat remappedCoordinateFar   = inverseQuaternionToReverseDirectionChange * unmappedCoordinateFar   * rotationToUpdateDirection;

    m_vertices.at(j)     = remappedCoordinateClose.x + startPointCoordinate.x;
    m_vertices.at(j + 1) = remappedCoordinateClose.y + startPointCoordinate.y;
    m_vertices.at(j + 2) = remappedCoordinateClose.z + startPointCoordinate.z;
    m_vertices.at(j + 3) = color.x;
    m_vertices.at(j + 4) = color.y;
    m_vertices.at(j + 5) = color.z;
    m_vertices.at(j + 6) = remappedCoordinateFar.x + startPointCoordinate.x;
    m_vertices.at(j + 7) = remappedCoordinateFar.y + startPointCoordinate.y;
    m_vertices.at(j + 8) = remappedCoordinateFar.z + startPointCoordinate.z;
    m_vertices.at(j + 9) = color.x;
    m_vertices.at(j + 10) = color.y;
    m_vertices.at(j + 11) = color.z;

		currentAngle += angle;
	}
}

void Cylinder::calculateIndices() {
	for (unsigned int i = 0; i < m_vertexCount; i++) {
		if (i % 2 == 0) {
			m_indices.at(i) = i;
		} else {
			m_indices.at(i) = 0;
		}
	}

	for (unsigned int i = 0; i < m_vertexCount; i++) {
		unsigned int j = m_vertexCount;
		m_indices.at(j + i) = i;
	}

	for (unsigned int i = 0; i < m_vertexCount; i++) {
		unsigned int j = 2 * m_vertexCount;
		if (i % 2 == 1) {
			m_indices.at(j + i) = i;
		} else {
			m_indices.at(j + i) = 1;
		}
	}
}
