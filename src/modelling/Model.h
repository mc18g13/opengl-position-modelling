#ifndef MODEL_H
#define MODEL_H

#include <future>
#include <vector>
#include <eigen3/Eigen/Dense>
#include "Timer.h"

class PathPlanner {
private:
  std::vector<Eigen::Vector3d> m_pathPoints;
  void calculateRandomPathPoints(int pointCount, Eigen::Vector3d startPoint, Eigen::Vector3d endpoint) {
    
  }
};

class InertialSensor {
private:
  Eigen::Vector3d m_data;
public:
  Eigen::Vector3d getData() {
    return m_data;
  }
};

class Gyroscope : public InertialSensor {
  
};

class Accelerometer : public InertialSensor {

};

class PositionEstimator {
private:
  Eigen::Vector3d m_position;
public:
  Eigen::Vector3d getPosition() {
    return m_position;
  }
};


class Model {
private:
  std::promise<void> m_exitSignal;
  std::future<void>  m_exitSignalFuture;
  std::thread        m_modellingThread;
  Timer              m_timer;

public:
  Model();
  ~Model();
  void execute();
  void stop();
  bool stopRequested();
  void waitForNextUpdateInterval(); 
};

#endif