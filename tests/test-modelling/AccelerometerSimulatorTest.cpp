#include "AccelerometerSimulator.h"
#include "AccelerometerSimulatorTest.h"

namespace {
  double deltaTimeSeconds = 0.001;
  const double errorForComparsionToBeTrue = 0.00001;

  void printPath(AccelerometerSimulator& instance, int size) {
    Eigen::IOFormat cleanFmt(4, 0, ", ", " ", "[", "]");
    for (int i = 0; i < size; ++i) {
      std::cout << instance.getDataFor(i).format(cleanFmt) << std::endl;
    }
  }
}

AccelerometerSimulatorTest::AccelerometerSimulatorTest() {

}

AccelerometerSimulatorTest::~AccelerometerSimulatorTest() {};

void AccelerometerSimulatorTest::SetUp() {};

void AccelerometerSimulatorTest::TearDown() {};

TEST_F(AccelerometerSimulatorTest, NoChangeInAttitudeProvideSameDataAsGravityVector) {
  std::vector<Eigen::Vector3d> path;
  path.push_back(Vector3d(0,0,0));
  path.push_back(Vector3d(0,0,0));
  path.push_back(Vector3d(0,0,0));
  AccelerometerSimulator simulator(path, deltaTimeSeconds);
  EXPECT_EQ(simulator.getDataFor(0), AccelerometerSimulator::GRAVITY);
}

TEST_F(AccelerometerSimulatorTest, NoChangeInPitchOrRollProvideSameDataAsGravityVector) {
  std::vector<Eigen::Vector3d> path;
  path.push_back(Vector3d(0,0,0));
  path.push_back(Vector3d(1,1,0));
  path.push_back(Vector3d(1,1,0));
  path.push_back(Vector3d(1,1,0));
  path.push_back(Vector3d(1,1,0));
  AccelerometerSimulator simulator(path, deltaTimeSeconds);

  std::cout << std::endl;
  printPath(simulator, path.size());

  for (int i = 0; i < 3; ++i) {
    ASSERT_NEAR(simulator.getDataFor(path.size() - 1)[i], AccelerometerSimulator::GRAVITY[i], errorForComparsionToBeTrue);
  }


}

TEST_F(AccelerometerSimulatorTest, PitchFrontUpGravityActsInXAxis) {
  std::vector<Eigen::Vector3d> path;
  path.push_back(Vector3d(0,0,0));
  path.push_back(Vector3d(0,0,1));
  path.push_back(Vector3d(0,0,1));
  path.push_back(Vector3d(0,0,1));
  path.push_back(Vector3d(0,0,1));
  AccelerometerSimulator simulator(path, deltaTimeSeconds);

  EXPECT_EQ(simulator.getDataFor(path.size() - 1), Vector3d(AccelerometerSimulator::GRAVITY[2],0,0));
}


TEST_F(AccelerometerSimulatorTest, RollRightGravityActsInYAxis) {
  std::vector<Eigen::Vector3d> path;
  path.push_back(Vector3d(0,0,0));
  path.push_back(Vector3d(0,1,0));
  path.push_back(Vector3d(0,1,1));
  path.push_back(Vector3d(1,1,1));
  path.push_back(Vector3d(1,1,1));
  path.push_back(Vector3d(1,1,1));
  AccelerometerSimulator simulator(path, deltaTimeSeconds);

  EXPECT_EQ(simulator.getDataFor(path.size() - 1), Vector3d(0,AccelerometerSimulator::GRAVITY[2],0));
}

TEST_F(AccelerometerSimulatorTest, ConstantVelocityProvidesGravityVector) {
  std::vector<Eigen::Vector3d> path;

  for (int i = 0; i < 6; ++i) {
    path.push_back(Vector3d(i,0,0));
  }

  AccelerometerSimulator simulator(path, deltaTimeSeconds);

  EXPECT_EQ(simulator.getDataFor(path.size() - 1), AccelerometerSimulator::GRAVITY);
}

TEST_F(AccelerometerSimulatorTest, ConstantLinearAccelerationProducesSameAccelerationAfterPathGenerated) {
  std::vector<Eigen::Vector3d> path;
  const double acceleration = 1;
  double previousVelocity = 0;
  double previousPosition = 0;
  for (int i = 0; i < 10; ++i) {
    double velocity = previousVelocity + acceleration * deltaTimeSeconds;
    double position = previousPosition + velocity * deltaTimeSeconds + acceleration * deltaTimeSeconds * deltaTimeSeconds / 2;

    path.push_back(Vector3d(position,0,0));

    previousVelocity = velocity;
    previousPosition = position;
  }

  AccelerometerSimulator simulator(path, deltaTimeSeconds);


  // printPath(simulator, path.size());
  
  const double errorForComparsionToBeTrue = 0.001;
  ASSERT_NEAR(simulator.getDataFor(path.size() - 1)[0], acceleration, errorForComparsionToBeTrue);
}

TEST_F(AccelerometerSimulatorTest, ConstantAccelerationPitchedUpProducesSameAccelerationAndGravity) {
  std::vector<Eigen::Vector3d> path;
  const double acceleration = 1000;
  double previousVelocity = 0;
  double previousPosition = 0;
  std::cout << std::fixed;
  std::cout << std::setprecision(14);

  for (int i = 0; i < 400; ++i) {
    double velocity = previousVelocity + acceleration * deltaTimeSeconds;
    double changeWithVelocity = velocity * deltaTimeSeconds;
    double changeWithAcceleration = acceleration * deltaTimeSeconds * deltaTimeSeconds / 2;
    double position = previousPosition + changeWithVelocity + changeWithAcceleration;

    path.push_back(Vector3d(0,0,position));


    previousVelocity = velocity;
    previousPosition = position;
  }

  AccelerometerSimulator simulator(path, deltaTimeSeconds);


  const double errorForComparsionToBeTrue = 0.001;
  ASSERT_NEAR(simulator.getDataFor(path.size() - 1)[0], acceleration + AccelerometerSimulator::GRAVITY[2], errorForComparsionToBeTrue);
}
