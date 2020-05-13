#include "PositionSensorSimulator.h"

PositionSensorSimulator::PositionSensorSimulator(std::vector<Vector3d> path, double deltaTimeSeconds) {
  m_data = path;
}