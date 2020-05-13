#ifndef PATH_PLANNER_H
#define PATH_PLANNER_H

#include <vector>
#include <Eigen/Dense>
#include <Eigen/Geometry>

class PathPlanner {
private:
  std::vector<Eigen::Vector3d> m_pathPoints;

public:
  PathPlanner();
  std::vector<Eigen::Vector3d> getPath();
private:
  void addPointToPath(const Eigen::Vector3d& nextPoint);
  void setupPathPoints(int pointCount);

  void addCircleOfPointsToPath(int pointCount);

  void printPathPoints();
};

#endif