#ifndef GYRO_SIUMULATOR_H
#define GYRO_SIUMULATOR_H

#include "SensorSimulator3D.h"

class GyroSimulator : public SensorSimulator3D { 
public:
  GyroSimulator(std::vector<Vector3d> path, double deltaTimeSeconds);
};

#endif