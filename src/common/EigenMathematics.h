
#ifndef EIGEN_MATHEMATICS_H
#define EIGEN_MATHEMATICS_H

#include <Eigen/Dense>
#include <Eigen/Geometry>

using Eigen::Vector3d;
using Eigen::Quaterniond;
using Eigen::Matrix3d;

class EigenMathematics {
public: 
  Quaterniond quaternionToGetFromOneOrientationToAnother(const Vector3d& from, const Vector3d& to);
  bool compareVectors(const Vector3d& v1, const Vector3d& v2, double errorForComparison = 0.0001);
};

#endif