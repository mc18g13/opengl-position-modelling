#ifndef ACCELEROMETER_SIUMULATOR_H
#define ACCELEROMETER_SIUMULATOR_H

#include "SensorSimulator3D.h"

class AccelerometerSimulator : public SensorSimulator3D { 
public:
  static const Vector3d GRAVITY;
  AccelerometerSimulator(std::vector<Vector3d> path, double deltaTimeSeconds);

private:
  Vector3d calculateLinearAccelerationFrom(
    const Vector3d& startPoint, const Vector3d& previousPoint, const Vector3d& thisPoint, double deltaTimeSeconds);
};

#endif