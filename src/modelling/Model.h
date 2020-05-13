#ifndef MODEL_H
#define MODEL_H

#include <future>
#include <vector>

#include <Eigen/Dense>
#include <Eigen/Geometry>

#include "PathPlanner.h"
#include "GyroSimulator.h"
#include "AccelerometerSimulator.h"
#include "PositionSensorSimulator.h"


class Model {
private:
  std::promise<void>                   m_exitSignal;
  std::future<void>                    m_exitSignalFuture;
  PathPlanner                          m_pathPlanner;
  GyroSimulator                        m_gyroSimulator;
  AccelerometerSimulator               m_accelerometerSimulator;
  PositionSensorSimulator              m_positionSensorSimulator;
  unsigned int                         m_pathIndex;
  std::promise<Eigen::Vector3d>        m_currentPosition;
  std::shared_future<Eigen::Vector3d>  m_currentPositionFuture;
  std::thread                          m_modellingThread;

  
public:
  Model();
  ~Model();
  void execute();
  void stop();
  std::shared_future<Eigen::Vector3d> getPosition();
  int getIndex();

private:
  bool stopRequested();
};

#endif