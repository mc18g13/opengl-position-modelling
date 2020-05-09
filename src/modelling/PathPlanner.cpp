#include "PathPlanner.h"

#include <cmath>
#include <math.h>
#include <iostream>

using Eigen::Vector3f;
using Eigen::Matrix3f;
using Eigen::Quaternionf;
using Eigen::AngleAxisf;


PathPlanner::PathPlanner() :
  m_pathPoints() {
  setupPathPoints(500);
}

std::vector<Eigen::Vector3f> PathPlanner::getPath() {
  return m_pathPoints;
}

void PathPlanner::addPointToPath(const Eigen::Vector3f& nextPoint) {
  m_pathPoints.push_back(nextPoint);
}

void PathPlanner::setupPathPoints(int pointCount) {
  addCircleOfPointsToPath(pointCount);
}

void PathPlanner::addCircleOfPointsToPath(int pointCount) {
  
  Matrix3f tiltPathUp(AngleAxisf(M_PI/8, Vector3f::UnitX() - Vector3f::UnitY()));

  Eigen::Vector3f firstPointOnCircleBeforeTranslation(-200,-200,0);
  float radius = firstPointOnCircleBeforeTranslation.norm();
  Eigen::Vector3f centreOfCircle(radius,radius,0);

  Eigen::Vector3f normalToPlaneCircleWillBeIn(Vector3f::UnitZ());
  constexpr float DEGREES_IN_CIRCLE = 360;
  constexpr float TO_RADIANS = 2 * M_PI / DEGREES_IN_CIRCLE;
  float angleChangeForPointCount = DEGREES_IN_CIRCLE / (float)pointCount;

  int eighthOfPathCount = pointCount / 8;
  for (int i = 0; i < eighthOfPathCount; ++i) {
    float amountToMoveForThisIteration = i * firstPointOnCircleBeforeTranslation.norm()/eighthOfPathCount;
    float nextXToFollowXAxis = amountToMoveForThisIteration;
    Eigen::Vector3f nextPointToFollowXAxis(nextXToFollowXAxis,0,0);
      
    addPointToPath(tiltPathUp * nextPointToFollowXAxis);
  }

  int sevenEighthPathCount = 7 * pointCount / 8;
  for (int i = eighthOfPathCount; i < sevenEighthPathCount; ++i) {

    float angle = (float)i * angleChangeForPointCount;
    float angleInRadians = angle * TO_RADIANS;
    float quaternionAngleInput = angleInRadians / 2;
    Eigen::Quaternionf rotation(
      std::cos(quaternionAngleInput), 
      std::sin(quaternionAngleInput) * normalToPlaneCircleWillBeIn[0], 
      std::sin(quaternionAngleInput) * normalToPlaneCircleWillBeIn[1], 
      std::sin(quaternionAngleInput) * normalToPlaneCircleWillBeIn[2]);

    Eigen::Quaternionf firstPointAsQuaternion;
    firstPointAsQuaternion.w()   = 0;
    firstPointAsQuaternion.vec() = firstPointOnCircleBeforeTranslation;

    Eigen::Quaternionf currentPointOnCircleAsQuaternion = rotation * firstPointAsQuaternion * rotation.inverse();    
    addPointToPath(tiltPathUp * (currentPointOnCircleAsQuaternion.vec() + centreOfCircle));
  }
  
  for (int i = 0; i < eighthOfPathCount; ++i) {
    float yStartPosition = firstPointOnCircleBeforeTranslation.norm();
    float amountToMoveForThisIteration = i * yStartPosition/eighthOfPathCount;
    float nextYToFollowYAxis = yStartPosition - amountToMoveForThisIteration;
    Eigen::Vector3f nextPointToFollowYAxis(0,nextYToFollowYAxis,0);
      
    addPointToPath(tiltPathUp * nextPointToFollowYAxis);
  }
}




void PathPlanner::printPathPoints() {
  Eigen::IOFormat cleanFmt(4, 0, ", ", " ", "[", "]");
  for (auto point : m_pathPoints) {
    std::cout << point.format(cleanFmt) << std::endl;
  }
}