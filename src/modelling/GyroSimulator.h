#ifndef GYRO_SIUMULATOR_H
#define GYRO_SIUMULATOR_H

#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <vector>

class GyroSimulator {
private:
public:
  GyroSimulator(std::vector<Eigen::Vector3f> path);

private:
  Eigen::Quaternionf quaternionToGetFromOneOrientationToAnother(const Eigen::Vector3f& v1, const Eigen::Vector3f& v2);
};

#endif