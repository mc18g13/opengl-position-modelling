#include "PositionSensorSimulator.h"

PositionSensorSimulator::PositionSensorSimulator(std::vector<Vector3f> path, float deltaTime) {
  m_data = path;
}