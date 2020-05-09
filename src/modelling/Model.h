#ifndef MODEL_H
#define MODEL_H

#include <future>
#include <vector>

#include <Eigen/Dense>
#include <Eigen/Geometry>

#include "PathPlanner.h"
#include "GyroSimulator.h"


class Model {
private:
  std::promise<void>                   m_exitSignal;
  std::future<void>                    m_exitSignalFuture;
  PathPlanner                          m_pathPlanner;
  GyroSimulator                        m_gyroSimulator;
  int                                  m_pathIndex;
  std::promise<Eigen::Vector3f>        m_currentPosition;
  std::shared_future<Eigen::Vector3f>  m_currentPositionFuture;
  std::thread                          m_modellingThread;

  
public:
  Model();
  ~Model();
  void execute();
  void stop();
  std::shared_future<Eigen::Vector3f> getPosition();
  int getIndex();

private:
  bool stopRequested();
};

#endif