#include "SensorSimulator3D.h"

Vector3d SensorSimulator3D::getDataFor(int index) {
  return m_data.at(index);
}
