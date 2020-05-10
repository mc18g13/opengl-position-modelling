#include "GyroSimulator.h"

GyroSimulator::GyroSimulator(std::vector<Vector3f> path, float deltaTime) {
  
  Quaternionf firstOrientation = quaternionToGetFromOneOrientationToAnother(Vector3f::UnitX(), Vector3f::UnitX());
  Vector3f firstEuler = firstOrientation.toRotationMatrix().eulerAngles(0, 1, 2);

  Vector3f firstEulerWithRespectToTime = firstEuler / deltaTime;
  m_data.push_back(firstEulerWithRespectToTime);
  
  for (int i = 1; i < path.size(); ++i) {
    Vector3f from = path.at(i - 1);
    Vector3f to   = path.at(i);

    Quaternionf rotationFromXAxisToLastVector = quaternionToGetFromOneOrientationToAnother(Vector3f::UnitX(), from);
    Quaternionf rotationFromXAxisToThisVector = quaternionToGetFromOneOrientationToAnother(Vector3f::UnitX(), to);
    Vector3f eulerLast = rotationFromXAxisToLastVector.toRotationMatrix().eulerAngles(0, 1, 2);
    Vector3f eulerThis = rotationFromXAxisToThisVector.toRotationMatrix().eulerAngles(0, 1, 2);
    
    Vector3f deltaEuler(eulerLast[0] - eulerThis[0], eulerLast[1] - eulerThis[1], eulerLast[2] - eulerThis[2]);
    Vector3f deltaEulerWithRespectToTime = deltaEuler / deltaTime;
    m_data.push_back(deltaEulerWithRespectToTime);

    // Eigen::IOFormat cleanFmt(4, 0, ", ", " ", "[", "]");
    // std::cout << eulerLast.format(cleanFmt) << std::endl;
    
    // std::cout << eulerThis.format(cleanFmt) << std::endl;
    // std::cout << deltaEulerWithRespectToTime.format(cleanFmt) << std::endl;
    
   
  }
  
}
