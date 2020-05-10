
#include "EigenMathematics.h"

Quaternionf EigenMathematics::quaternionToGetFromOneOrientationToAnother(const Vector3f& from, const Vector3f& to) {

  Vector3f a = from.cross(to);

  Quaternionf q;
  q.vec() = a;
  q.w() = sqrt((from.norm() * from.norm()) * (to.norm() * to.norm())) + from.dot(to);
  return q;
}
