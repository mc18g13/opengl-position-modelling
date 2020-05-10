#include "SensorSimulator3D.h"

Vector3f SensorSimulator3D::getDataFor(int index) {
  return m_data.at(index);
}
