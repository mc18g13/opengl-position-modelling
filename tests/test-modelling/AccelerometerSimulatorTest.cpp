#include "AccelerometerSimulator.h"
#include "AccelerometerSimulatorTest.h"

namespace {
  float deltaTimeSeconds = 0.001;
}

AccelerometerSimulatorTest::AccelerometerSimulatorTest() {

}

AccelerometerSimulatorTest::~AccelerometerSimulatorTest() {};

void AccelerometerSimulatorTest::SetUp() {};

void AccelerometerSimulatorTest::TearDown() {};

TEST_F(AccelerometerSimulatorTest, NoChangeInAttitudeProvideSameDataAsGravityVector) {
  std::vector<Eigen::Vector3f> path;
  path.push_back(Vector3f(0,0,0));
  path.push_back(Vector3f(0,0,0));
  path.push_back(Vector3f(0,0,0));
AccelerometerSimulator simulator(path, deltaTimeSeconds);

  EXPECT_EQ(simulator.getDataFor(0), AccelerometerSimulator::GRAVITY);
}

TEST_F(AccelerometerSimulatorTest, NoChangeInPitchOrRollProvideSameDataAsGravityVector) {
  std::vector<Eigen::Vector3f> path;
  path.push_back(Vector3f(0,0,0));
  path.push_back(Vector3f(1,1,0));
  path.push_back(Vector3f(1,1,0));
  path.push_back(Vector3f(1,1,0));
  path.push_back(Vector3f(1,1,0));
  AccelerometerSimulator simulator(path, deltaTimeSeconds);

  EXPECT_EQ(simulator.getDataFor(path.size() - 1), AccelerometerSimulator::GRAVITY);
}

TEST_F(AccelerometerSimulatorTest, PitchFrontUpGravityActsInXAxis) {
  std::vector<Eigen::Vector3f> path;
  path.push_back(Vector3f(0,0,0));
  path.push_back(Vector3f(0,0,1));
  path.push_back(Vector3f(0,0,1));
  path.push_back(Vector3f(0,0,1));
  path.push_back(Vector3f(0,0,1));
  AccelerometerSimulator simulator(path, deltaTimeSeconds);

  EXPECT_EQ(simulator.getDataFor(path.size() - 1), Vector3f(AccelerometerSimulator::GRAVITY[2],0,0));
}


TEST_F(AccelerometerSimulatorTest, RollRightGravityActsInYAxis) {
  std::vector<Eigen::Vector3f> path;
  path.push_back(Vector3f(0,0,0));
  path.push_back(Vector3f(0,1,0));
  path.push_back(Vector3f(0,1,1));
  path.push_back(Vector3f(1,1,1));
  path.push_back(Vector3f(1,1,1));
  path.push_back(Vector3f(1,1,1));
  AccelerometerSimulator simulator(path, deltaTimeSeconds);

  EXPECT_EQ(simulator.getDataFor(path.size() - 1), Vector3f(0,AccelerometerSimulator::GRAVITY[2],0));
}

