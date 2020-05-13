
#include "EigenMathematics.h"

Quaterniond EigenMathematics::quaternionToGetFromOneOrientationToAnother(const Vector3d& from, const Vector3d& to) {

  Vector3d a = to.cross(from);

  Quaterniond q;
  q.vec() = a;
  q.w() = sqrt((from.norm() * from.norm()) * (to.norm() * to.norm())) + from.dot(to);
  return q;
}

bool EigenMathematics::compareVectors(const Vector3d& v1, const Vector3d& v2, double errorForComparison) {
  Vector3d difference = v1 - v2;

  for (int i = 0; i < 3; i++) {
    bool thisComponentIsWithinRange = abs(difference[i]) < errorForComparison;
    if (!thisComponentIsWithinRange) {
      return false;
    }
  }

  return true;
}