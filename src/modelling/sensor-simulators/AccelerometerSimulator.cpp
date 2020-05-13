#include "AccelerometerSimulator.h"

namespace {
  Eigen::IOFormat cleanFmt(4, 0, ", ", " ", "[", "]");
}

const Vector3d AccelerometerSimulator::GRAVITY(0,0,-9.80665);

AccelerometerSimulator::AccelerometerSimulator(std::vector<Vector3d> path, double deltaTimeSeconds) {
  
  Vector3d previousHeading(Vector3d::UnitX());
  Vector3d currentHeading(Vector3d::UnitX());

  Quaterniond gravityQuaternion;
  gravityQuaternion.w() = 0;
  gravityQuaternion.vec() = GRAVITY;

  Quaterniond rotatedGravityQuaternion(gravityQuaternion);
  
  const int indexAtWhichAccelerationCanBeCalcalulated = 2;
  for (int i = 0; i < path.size(); ++i) {

    Vector3d startPoint;
    Vector3d previousPoint;

    if (i < indexAtWhichAccelerationCanBeCalcalulated) {
      startPoint    = path.at(0);
      previousPoint = path.at(0);
    } else {
      startPoint    = path.at(i - 2);
      previousPoint = path.at(i - 1);
    }

    Vector3d thisPoint = path.at(i);

    if (thisPoint != previousPoint) {
      currentHeading = (thisPoint - previousPoint).normalized();
    }

    Quaterniond orientationChangeSinceLastHeadingUpdate = quaternionToGetFromOneOrientationToAnother(previousHeading, currentHeading);
    orientationChangeSinceLastHeadingUpdate = orientationChangeSinceLastHeadingUpdate.normalized();

    Quaterniond quaternionOfLinearAcceleration;
    quaternionOfLinearAcceleration.vec() = calculateLinearAccelerationFrom(startPoint, previousPoint, thisPoint, deltaTimeSeconds);
    quaternionOfLinearAcceleration.w()   = 0;

    Quaterniond orientationChangeFromOrigin = quaternionToGetFromOneOrientationToAnother(Vector3d::UnitX(), currentHeading);
    orientationChangeFromOrigin = orientationChangeFromOrigin.normalized();
    
    Quaterniond quaternionOfLinearAccelerationRotated = 
      orientationChangeFromOrigin * quaternionOfLinearAcceleration * orientationChangeFromOrigin.inverse();

    Vector3d linearAcceleration  = quaternionOfLinearAccelerationRotated.vec();
    
    rotatedGravityQuaternion = orientationChangeSinceLastHeadingUpdate * rotatedGravityQuaternion * orientationChangeSinceLastHeadingUpdate.inverse();
    Vector3d rotatedGravityVector = rotatedGravityQuaternion.vec();

    Vector3d combinedAcceleration = linearAcceleration + rotatedGravityVector;
    m_data.push_back(combinedAcceleration);

    previousHeading = currentHeading;

  }
  
}

#include <iomanip>
Vector3d AccelerometerSimulator::calculateLinearAccelerationFrom(
  const Vector3d& startPoint, const Vector3d& previousPoint, const Vector3d& thisPoint, double deltaTimeSeconds) {

  std::cout << std::fixed;
  std::cout << std::setprecision(14);

  Vector3d startPointDouble(startPoint[0],startPoint[1],startPoint[2]);
  Vector3d previousPointDouble(previousPoint[0],previousPoint[1],previousPoint[2]);
  Vector3d thisPointDouble(thisPoint[0],thisPoint[1],thisPoint[2]);

  double frequency = 1 / deltaTimeSeconds;
  Vector3d lastDeltaPosition = previousPointDouble - startPointDouble;
  Vector3d lastVelocity      = lastDeltaPosition * frequency;
  
  Vector3d thisDeltaPosition = thisPointDouble - previousPointDouble;
  Vector3d thisVelocity      = thisDeltaPosition * frequency;

  // std::cout << thisDeltaPosition[2] << std::endl;

  Vector3d deltaVelocity = thisVelocity - lastVelocity;
  // std::cout << deltaVelocity.format(cleanFmt) << std::endl;
  double dividy = deltaVelocity[2] * frequency;
  // std::cout << deltaVelocity[2] << std::endl;
  // if (abs(dividy - 1)  < 0.01) {
  //   std::cout << "shitt" << std::endl;
  // }
  Vector3d acceleration  = deltaVelocity * frequency;

  // std::cout << (deltaVelocity * frequency).format(cleanFmt) << std::endl;


  return Vector3d((double)acceleration[0],(double)acceleration[1],(double)acceleration[2]);
}