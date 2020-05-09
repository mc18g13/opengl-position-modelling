#include "GyroSimulator.h"
#include <iostream>
using Eigen::Vector3f;
using Eigen::Quaternionf;

namespace {

}

GyroSimulator::GyroSimulator(std::vector<Vector3f> path) {

  for (int i = 1; i < path.size(); ++i) {
    Vector3f from = path.at(i - 1);
    Vector3f to   = path.at(i);

    Quaternionf rotationFromXAxisToLastVector = quaternionToGetFromOneOrientationToAnother(Vector3f::UnitX(), from);
    Quaternionf rotationFromXAxisToThisVector = quaternionToGetFromOneOrientationToAnother(Vector3f::UnitX(), to);
    Vector3f eulerLast = rotationFromXAxisToLastVector.toRotationMatrix().eulerAngles(0, 1, 2);
    Vector3f eulerThis = rotationFromXAxisToThisVector.toRotationMatrix().eulerAngles(0, 1, 2);
    std::cout << "euler " << eulerLast[0] - eulerThis[0] << " " << eulerLast[1] - eulerThis[1] << " " << eulerLast[2] - eulerThis[2] << std::endl;
  }
  
}

Quaternionf GyroSimulator::quaternionToGetFromOneOrientationToAnother(const Vector3f& from, const Vector3f& to) {

  Vector3f a = from.cross(to);

  Quaternionf q;
  q.vec() = a;
  q.w() = sqrt((from.norm() * from.norm()) * (to.norm() * to.norm())) + from.dot(to);
  return q;
}
