#include "GyroSimulator.h"

GyroSimulator::GyroSimulator(std::vector<Vector3d> path, double deltaTimeSeconds) {
  
  Quaterniond firstOrientation = quaternionToGetFromOneOrientationToAnother(Vector3d::UnitX(), Vector3d::UnitX());
  Vector3d firstEuler = firstOrientation.toRotationMatrix().eulerAngles(0, 1, 2);

  Vector3d firstEulerWithRespectToTime = firstEuler / deltaTimeSeconds;
  m_data.push_back(firstEulerWithRespectToTime);
  
  for (int i = 1; i < path.size(); ++i) {
    Vector3d from = path.at(i - 1);
    Vector3d to   = path.at(i);

    Quaterniond rotationFromXAxisToLastVector = quaternionToGetFromOneOrientationToAnother(Vector3d::UnitX(), from);
    Quaterniond rotationFromXAxisToThisVector = quaternionToGetFromOneOrientationToAnother(Vector3d::UnitX(), to);
    Vector3d eulerLast = rotationFromXAxisToLastVector.toRotationMatrix().eulerAngles(0, 1, 2);
    Vector3d eulerThis = rotationFromXAxisToThisVector.toRotationMatrix().eulerAngles(0, 1, 2);
    
    Vector3d deltaEuler(eulerLast[0] - eulerThis[0], eulerLast[1] - eulerThis[1], eulerLast[2] - eulerThis[2]);
    Vector3d deltaEulerWithRespectToTime = deltaEuler / deltaTimeSeconds;
    m_data.push_back(deltaEulerWithRespectToTime);

    // Eigen::IOFormat cleanFmt(4, 0, ", ", " ", "[", "]");
    // std::cout << eulerLast.format(cleanFmt) << std::endl;
    
    // std::cout << eulerThis.format(cleanFmt) << std::endl;
    // std::cout << deltaEulerWithRespectToTime.format(cleanFmt) << std::endl;
    
   
  }
  
}
