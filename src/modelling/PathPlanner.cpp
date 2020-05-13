#include "PathPlanner.h"

#include <cmath>
#include <math.h>
#include <iostream>

using Eigen::Vector3d;
using Eigen::Quaterniond;
using Eigen::AngleAxisd;
using Eigen::Matrix3d;


PathPlanner::PathPlanner() :
  m_pathPoints() {
  setupPathPoints(2000);
}

std::vector<Eigen::Vector3d> PathPlanner::getPath() {
  return m_pathPoints;
}

void PathPlanner::addPointToPath(const Eigen::Vector3d& nextPoint) {
  m_pathPoints.push_back(nextPoint);
}

void PathPlanner::setupPathPoints(int pointCount) {
  addCircleOfPointsToPath(pointCount);
}

void PathPlanner::addCircleOfPointsToPath(int pointCount) {
  
  Matrix3d tiltPathUp(AngleAxisd(M_PI/8, Vector3d::UnitX() - Vector3d::UnitY()));

  Eigen::Vector3d firstPointOnCircleBeforeTranslation(-200,-200,0);
  double radius = firstPointOnCircleBeforeTranslation.norm();
  Eigen::Vector3d centreOfCircle(radius,radius,0);

  Eigen::Vector3d normalToPlaneCircleWillBeIn(Vector3d::UnitZ());
  constexpr double DEGREES_IN_CIRCLE = 360;
  constexpr double TO_RADIANS = 2 * M_PI / DEGREES_IN_CIRCLE;
  double angleChangeForPointCount = DEGREES_IN_CIRCLE / (double)pointCount;

  int eighthOfPathCount = pointCount / 8;
  for (int i = 0; i < eighthOfPathCount; ++i) {
    double amountToMoveForThisIteration = i * firstPointOnCircleBeforeTranslation.norm()/eighthOfPathCount;
    double nextXToFollowXAxis = amountToMoveForThisIteration;
    Eigen::Vector3d nextPointToFollowXAxis(nextXToFollowXAxis,0,0);
      
    addPointToPath(tiltPathUp * nextPointToFollowXAxis);
  }

  int sevenEighthPathCount = 7 * pointCount / 8;
  for (int i = eighthOfPathCount; i < sevenEighthPathCount; ++i) {

    double angle = (double)i * angleChangeForPointCount;
    double angleInRadians = angle * TO_RADIANS;
    double quaternionAngleInput = angleInRadians / 2;
    Eigen::Quaterniond rotation(
      std::cos(quaternionAngleInput), 
      std::sin(quaternionAngleInput) * normalToPlaneCircleWillBeIn[0], 
      std::sin(quaternionAngleInput) * normalToPlaneCircleWillBeIn[1], 
      std::sin(quaternionAngleInput) * normalToPlaneCircleWillBeIn[2]);

    Eigen::Quaterniond firstPointAsQuaternion;
    firstPointAsQuaternion.w()   = 0;
    firstPointAsQuaternion.vec() = firstPointOnCircleBeforeTranslation;

    Eigen::Quaterniond currentPointOnCircleAsQuaternion = rotation * firstPointAsQuaternion * rotation.inverse();    
    addPointToPath(tiltPathUp * (currentPointOnCircleAsQuaternion.vec() + centreOfCircle));
  }
  
  for (int i = 0; i < eighthOfPathCount; ++i) {
    double yStartPosition = firstPointOnCircleBeforeTranslation.norm();
    double amountToMoveForThisIteration = i * yStartPosition/eighthOfPathCount;
    double nextYToFollowYAxis = yStartPosition - amountToMoveForThisIteration;
    Eigen::Vector3d nextPointToFollowYAxis(0,nextYToFollowYAxis,0);
      
    addPointToPath(tiltPathUp * nextPointToFollowYAxis);
  }
}




void PathPlanner::printPathPoints() {
  Eigen::IOFormat cleanFmt(4, 0, ", ", " ", "[", "]");
  for (auto point : m_pathPoints) {
    std::cout << point.format(cleanFmt) << std::endl;
  }
}