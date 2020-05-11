#ifndef POSITION_SENSOR_SIMULATOR_H
#define POSITION_SENSOR_SIMULATOR_H

#include "SensorSimulator3D.h"

class PositionSensorSimulator : public SensorSimulator3D {
public:
  PositionSensorSimulator(std::vector<Vector3f> path, float deltaTimeSeconds);
};

#endif