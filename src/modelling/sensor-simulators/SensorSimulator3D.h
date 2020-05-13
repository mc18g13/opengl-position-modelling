#ifndef SENSOR_SIMULATOR_3D_H
#define SENSOR_SIMULATOR_3D_H

#include <vector>
#include <iostream>

#include "EigenMathematics.h"

class SensorSimulator3D : public EigenMathematics {
protected:
  std::vector<Vector3d> m_data;

public:
  Vector3d getDataFor(int index);
};

#endif