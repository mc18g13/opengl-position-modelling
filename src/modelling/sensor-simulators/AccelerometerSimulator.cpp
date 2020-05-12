#include "AccelerometerSimulator.h"

namespace {
  Eigen::IOFormat cleanFmt(4, 0, ", ", " ", "[", "]");
}

const Vector3f AccelerometerSimulator::GRAVITY(0,0,-9.80665);

AccelerometerSimulator::AccelerometerSimulator(std::vector<Vector3f> path, float deltaTimeSeconds) {
  
  Vector3f previousHeading(Vector3f::UnitX());
  Vector3f currentHeading(Vector3f::UnitX());

  Quaternionf gravityQuaternion;
  gravityQuaternion.w() = 0;
  gravityQuaternion.vec() = GRAVITY;

  Quaternionf rotatedGravityQuaternion(gravityQuaternion);
  
  const int indexAtWhichAccelerationCanBeCalcalulated = 2;
  for (int i = 0; i < path.size(); ++i) {

    Vector3f startPoint;
    Vector3f previousPoint;

    if (i < indexAtWhichAccelerationCanBeCalcalulated) {
      startPoint    = path.at(0);
      previousPoint = path.at(0);
    } else {
      startPoint    = path.at(i - 2);
      previousPoint = path.at(i - 1);
    }

    Vector3f thisPoint = path.at(i);

    if (thisPoint != previousPoint) {
      currentHeading = thisPoint - previousPoint;
    }

    std::cout << previousHeading.format(cleanFmt) << " " << currentHeading.format(cleanFmt) << std::endl; 
    std::cout << previousHeading.format(cleanFmt) << " " << currentHeading.format(cleanFmt) << std::endl; 
    std::cout << previousHeading.format(cleanFmt) << " " << currentHeading.format(cleanFmt) << std::endl; 
    std::cout << previousHeading.format(cleanFmt) << " " << currentHeading.format(cleanFmt) << std::endl; 

    Vector3f linearAcceleration  = calculateLinearAccelerationFrom(startPoint, previousPoint, thisPoint, deltaTimeSeconds);
    Quaternionf orientationOfGravityVector = quaternionToGetFromOneOrientationToAnother(previousHeading, currentHeading);
    rotatedGravityQuaternion = orientationOfGravityVector.inverse() * rotatedGravityQuaternion * orientationOfGravityVector;
    Vector3f rotatedGravityVector = rotatedGravityQuaternion.vec();

    Vector3f combinedAcceleration = linearAcceleration + rotatedGravityVector;
    m_data.push_back(combinedAcceleration);

    previousHeading = currentHeading;

  }
  
}


Vector3f AccelerometerSimulator::calculateLinearAccelerationFrom(
  const Vector3f& startPoint, const Vector3f& previousPoint, const Vector3f& thisPoint, float deltaTimeSeconds) {
  Vector3f lastDeltaPosition = previousPoint - startPoint;
  Vector3f lastVelocity      = lastDeltaPosition / deltaTimeSeconds;
  
  Vector3f thisDeltaPosition = thisPoint - previousPoint;
  Vector3f thisVelocity      = thisDeltaPosition / deltaTimeSeconds;

  Vector3f deltaVelocity = thisVelocity - lastVelocity;
  Vector3f acceleration  = deltaVelocity / deltaTimeSeconds;

  return acceleration;
}