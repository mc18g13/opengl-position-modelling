#include "AccelerometerSimulator.h"

const Vector3f AccelerometerSimulator::GRAVITY(0,0,-9.80665);

AccelerometerSimulator::AccelerometerSimulator(std::vector<Vector3f> path, float deltaTimeSeconds) {
  
  Vector3f currentHeading(Vector3f::UnitX());


  Quaternionf gravityQuaternion;
  gravityQuaternion.w() = 0;
  gravityQuaternion.vec() = GRAVITY;

  Vector3f linearAcceleration  = calculateLinearAccelerationFrom(path.at(0), path.at(0), path.at(0), deltaTimeSeconds);
  m_data.push_back(linearAcceleration + GRAVITY);


  if (path.at(1) != path.at(0)) {
    currentHeading = path.at(1) - path.at(0);
  }

  linearAcceleration  = calculateLinearAccelerationFrom(path.at(0), path.at(0), path.at(1), deltaTimeSeconds);
  Quaternionf orientationOfGravityVector = quaternionToGetFromOneOrientationToAnother(Vector3f::UnitX(), currentHeading);
  Vector3f rotatedGravityVector = (orientationOfGravityVector * gravityQuaternion * orientationOfGravityVector.inverse()).vec();

  m_data.push_back(linearAcceleration + rotatedGravityVector);
  
  for (int i = 2; i < path.size(); ++i) {
    Vector3f startPoint    = path.at(i - 2);
    Vector3f previousPoint = path.at(i - 1);
    Vector3f thisPoint     = path.at(i);

    if (thisPoint != previousPoint) {
      currentHeading = thisPoint - previousPoint;
    }

    Vector3f linearAcceleration  = calculateLinearAccelerationFrom(startPoint, previousPoint, thisPoint, deltaTimeSeconds);
    Quaternionf orientationOfGravityVector = quaternionToGetFromOneOrientationToAnother(Vector3f::UnitX(), currentHeading);
    Vector3f rotatedGravityVector = (orientationOfGravityVector * gravityQuaternion * orientationOfGravityVector.inverse()).vec();

    Vector3f combinedAcceleration = linearAcceleration + rotatedGravityVector;
    m_data.push_back(combinedAcceleration);


    // Eigen::IOFormat cleanFmt(4, 0, ", ", " ", "[", "]");

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