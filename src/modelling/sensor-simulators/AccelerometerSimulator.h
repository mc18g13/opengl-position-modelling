#ifndef ACCELEROMETER_SIUMULATOR_H
#define ACCELEROMETER_SIUMULATOR_H

#include "SensorSimulator3D.h"

class AccelerometerSimulator : public SensorSimulator3D { 
public:
  static const Vector3f GRAVITY;
  AccelerometerSimulator(std::vector<Vector3f> path, float deltaTimeSeconds);

private:
  Vector3f calculateLinearAccelerationFrom(
    const Vector3f& startPoint, const Vector3f& previousPoint, const Vector3f& thisPoint, float deltaTimeSeconds);
};

#endif