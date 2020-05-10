#include "AccelerometerSimulator.h"



AccelerometerSimulator::AccelerometerSimulator(std::vector<Vector3f> path, float deltaTime) {
  

  Vector3f gravity(0,0,-9.80665);
  Quaternionf gravityQuaternion;
  gravityQuaternion.w() = 0;
  gravityQuaternion.vec() = gravity;
  Vector3f initialAccelerationVector(0,0,0);

  Vector3f linearAcceleration  = calculateLinearAccelerationFrom(initialAccelerationVector, initialAccelerationVector, path.at(0), deltaTime);
  m_data.push_back(linearAcceleration + gravity);

  Quaternionf orientationOfGravityVector = quaternionToGetFromOneOrientationToAnother(Vector3f::UnitX(), path.at(1) - path.at(0));
  Vector3f rotatedGravityVector = (orientationOfGravityVector * gravityQuaternion * orientationOfGravityVector.inverse()).vec();


  linearAcceleration  = calculateLinearAccelerationFrom(initialAccelerationVector, path.at(0), path.at(1), deltaTime);
  m_data.push_back(linearAcceleration);
  
  for (int i = 2; i < path.size(); ++i) {
    Vector3f startPoint    = path.at(i - 2);
    Vector3f previousPoint = path.at(i - 1);
    Vector3f thisPoint     = path.at(i);

    Vector3f linearAcceleration  = calculateLinearAccelerationFrom(startPoint, previousPoint, thisPoint, deltaTime);
    m_data.push_back(linearAcceleration);


    // Eigen::IOFormat cleanFmt(4, 0, ", ", " ", "[", "]");
    // std::cout << thisVelocity.norm() << " " << lastVelocity.norm() << " " << acceleration.norm() << std::endl;
  }
  
}


Vector3f AccelerometerSimulator::calculateLinearAccelerationFrom(
  const Vector3f& startPoint, const Vector3f& previousPoint, const Vector3f& thisPoint, float deltaTime) {
  Vector3f lastDeltaPosition = previousPoint - startPoint;
  Vector3f lastVelocity      = lastDeltaPosition / deltaTime;
  
  Vector3f thisDeltaPosition = thisPoint - previousPoint;
  Vector3f thisVelocity      = thisDeltaPosition / deltaTime;

  Vector3f deltaVelocity = thisVelocity - lastVelocity;
  Vector3f acceleration  = deltaVelocity / deltaTime;

  return acceleration;
}