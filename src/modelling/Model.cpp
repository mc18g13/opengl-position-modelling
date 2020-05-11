#include "Model.h"
#include <chrono>
#include <iostream>

using Eigen::Vector3f;

namespace {
  constexpr double SECONDS_TO_MILLIS  = 1000;
  constexpr double UPDATE_FREQUENCY   = 4;
  constexpr double UPDATE_INTERVAL_S  = 1 / UPDATE_FREQUENCY;
  constexpr double UPDATE_INTERVAL_MS = UPDATE_INTERVAL_S * SECONDS_TO_MILLIS; 
}

Model::Model() :
  m_exitSignal(),
  m_exitSignalFuture(m_exitSignal.get_future()),
  m_pathPlanner(),
  m_gyroSimulator(m_pathPlanner.getPath(), UPDATE_INTERVAL_S),
  m_accelerometerSimulator(m_pathPlanner.getPath(), UPDATE_INTERVAL_S),
  m_positionSensorSimulator(m_pathPlanner.getPath(), UPDATE_INTERVAL_S),
  m_pathIndex(0),
  m_currentPosition(),
  m_currentPositionFuture(m_currentPosition.get_future()),
  m_modellingThread(&Model::execute, this) {
}

Model::~Model() {
  if (m_modellingThread.joinable()) {
    m_modellingThread.join();
  }
}

void Model::execute() {
  while (!stopRequested()) {
    std::vector<Vector3f> path = m_pathPlanner.getPath();
    

    if (m_pathIndex < path.size()) {
      
    }
    // Vector3f position = m_positionSensorSimulator.getDataFor(m_pathIndex);
      
    
    if (m_pathIndex < path.size()) {
      Vector3f pathPoint = path.at(m_pathIndex);
      
      if (m_currentPositionFuture.valid() ) {
        
        bool currentPositionShouldBeUpdated = 
          m_currentPositionFuture.wait_for(std::chrono::milliseconds(0)) == std::future_status::timeout;
        
        if (currentPositionShouldBeUpdated) {
          m_currentPosition.set_value(pathPoint);
        }
      } else {
        std::cout << "not valid" << std::endl;
      }

      
    }

  }
}

void Model::stop() {
  std::cout << "model set to stop" << std::endl;
  m_exitSignal.set_value();
}

std::shared_future<Vector3f> Model::getPosition() {
  m_pathIndex++;
  m_currentPosition = std::promise<Vector3f>();
  m_currentPositionFuture = m_currentPosition.get_future();
  return m_currentPositionFuture;
}

int Model::getIndex() {
  return m_pathIndex;
}

bool Model::stopRequested() {
  bool stopIsRequested = 
    m_exitSignalFuture.wait_for(std::chrono::milliseconds(0)) != std::future_status::timeout;
  return stopIsRequested;
}