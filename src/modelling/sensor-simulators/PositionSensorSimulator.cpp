#include "PositionSensorSimulator.h"

PositionSensorSimulator::PositionSensorSimulator(std::vector<Vector3f> path, float deltaTimeSeconds) {
  m_data = path;
}