#include "Model.h"
#include <chrono>
#include <iostream>
#include <unistd.h>

namespace {
  constexpr double SECONDS_TO_MILLIS  = 1000;
  constexpr double UPDATE_FREQUENCY   = 50;
  constexpr double UPDATE_INTERVAL_S  = 1 / UPDATE_FREQUENCY;
  constexpr double UPDATE_INTERVAL_MS = UPDATE_INTERVAL_S * SECONDS_TO_MILLIS; 
}

Model::Model() :
  m_exitSignal(),
  m_exitSignalFuture(m_exitSignal.get_future()),
  m_modellingThread(&Model::execute, this),
  m_timer() {

}

Model::~Model() {
  if (m_modellingThread.joinable()) {
    m_modellingThread.join();
  }
}

void Model::execute() {
  while (!stopRequested()) {
    waitForNextUpdateInterval();

    std::cout << "model is running " << std::endl;
  }
}

void Model::stop() {
  std::cout << "model set to stop" << std::endl;
  m_exitSignal.set_value();
}

bool Model::stopRequested() {
  bool stopIsRequested = 
    m_exitSignalFuture.wait_for(std::chrono::milliseconds(0)) != std::future_status::timeout;
  return stopIsRequested;
}

void Model::waitForNextUpdateInterval() {
  while (m_timer.elapsed() < UPDATE_INTERVAL_MS);
  std::cout << "waited" << std::endl;
  m_timer.reset();
}