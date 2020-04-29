#include <Orientation.h>
#include <iostream>
Orientation::Orientation() {
//	const static unsigned int m_vertexCount = 6;
	setup(6, 6);

	float verticesBuffer[36] = {
		0.0f  , 0.0f  , 0.0f  , 1.000f,  0.000f,  0.000f,
		100.0f, 0.0f  , 0.0f  , 1.000f,  0.000f,  0.000f,
		0.0f  , 0.0f  , 0.0f  , 0.000f,  1.000f,  0.000f,
		0.0f  , 100.0f, 0.0f  , 0.000f,  1.000f,  0.000f,
		0.0f  , 0.0f  , 0.0f  , 0.000f,  0.000f,  1.000f,
		0.0f  , 0.0f  , 100.0f, 0.000f,  0.000f,  1.000f,
	 };

	unsigned int indicesBuffer[6] = {
		0,1,
		2,3,
		4,5
	};

	for (int i = 0; i < 6; i++) {
		int index = i * 6;

		m_vertices.at(index	   ) = verticesBuffer[index];
		m_vertices.at(index + 1) = verticesBuffer[index + 1];
		m_vertices.at(index + 2) = verticesBuffer[index + 2];
		m_vertices.at(index + 3) = verticesBuffer[index + 3];
		m_vertices.at(index + 4) = verticesBuffer[index + 4];
		m_vertices.at(index + 5) = verticesBuffer[index + 5];

		m_indices.at(i) = indicesBuffer[i];

	}

}

Orientation::~Orientation() {
	// TODO Auto-generated destructor stub
}
