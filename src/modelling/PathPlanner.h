#ifndef PATH_PLANNER_H
#define PATH_PLANNER_H

#include <vector>
#include <Eigen/Dense>
#include <Eigen/Geometry>

class PathPlanner {
private:
  std::vector<Eigen::Vector3f> m_pathPoints;

public:
  PathPlanner();
  std::vector<Eigen::Vector3f> getPath();
private:
  void addPointToPath(const Eigen::Vector3f& nextPoint);
  void setupPathPoints(int pointCount);

  void addCircleOfPointsToPath(int pointCount);

  void printPathPoints();
};

#endif