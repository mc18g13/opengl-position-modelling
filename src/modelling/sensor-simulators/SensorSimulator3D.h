#ifndef SENSOR_SIMULATOR_3D_H
#define SENSOR_SIMULATOR_3D_H

#include <vector>
#include <iostream>

#include "EigenMathematics.h"

class SensorSimulator3D : public EigenMathematics {
protected:
  std::vector<Vector3f> m_data;

public:
  Vector3f getDataFor(int index);
};

#endif