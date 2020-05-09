#include "GyroSimulator.h"

using Eigen::Vector3f;
using Eigen::Quaternionf;

GyroSimulator::GyroSimulator(std::vector<Vector3f> path) {

  for (int i = 1; i < path.size(); ++i) {
    Vector3f from = path.at(i - 1);
    Vector3f to = path.at(i);
  }
  
}

Quaternionf GyroSimulator::quaternionToGetFromOneOrientationToAnother(const Vector3f& from, const Vector3f& to) {

  Vector3f a = from.cross(to);

  Quaternionf q;
  q.vec() = a;
  q.w() = sqrt((from.norm() * from.norm()) * (to.norm() * to.norm())) + from.dot(to);
  return q;
}
