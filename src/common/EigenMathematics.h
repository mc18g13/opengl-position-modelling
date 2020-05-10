
#ifndef EIGEN_MATHEMATICS_H
#define EIGEN_MATHEMATICS_H

#include <Eigen/Dense>
#include <Eigen/Geometry>

using Eigen::Vector3f;
using Eigen::Quaternionf;
using Eigen::Matrix3f;

class EigenMathematics {
public: 
  Quaternionf quaternionToGetFromOneOrientationToAnother(const Vector3f& from, const Vector3f& to);
};

#endif