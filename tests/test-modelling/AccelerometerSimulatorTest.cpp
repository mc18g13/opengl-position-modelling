// #include "foo.h"
#include "AccelerometerSimulator.h"
#include "AccelerometerSimulatorTest.h"

using ::testing::Return;

AccelerometerSimulatorTest::AccelerometerSimulatorTest() {
//     // Have qux return true by default
//     ON_CALL(m_bar,qux()).WillByDefault(Return(true));
//     // Have norf return false by default
//     ON_CALL(m_bar,norf()).WillByDefault(Return(false));
}

AccelerometerSimulatorTest::~AccelerometerSimulatorTest() {};

void AccelerometerSimulatorTest::SetUp() {};

void AccelerometerSimulatorTest::TearDown() {};

TEST_F(AccelerometerSimulatorTest, NoChangeInAttitudeProvideSameDataAsGravityVector) {
  std::vector<Eigen::Vector3f> path;
  path.push_back(Vector3f(0,0,0));
  path.push_back(Vector3f(0,0,0));
  path.push_back(Vector3f(0,0,0));
  AccelerometerSimulator simulator(path, 0.001);

  EXPECT_EQ(simulator.getDataFor(0), AccelerometerSimulator::GRAVITY);
}

TEST_F(AccelerometerSimulatorTest, NoChangeInPitchOrRollProvideSameDataAsGravityVector) {
  std::vector<Eigen::Vector3f> path;
  path.push_back(Vector3f(0,0,0));
  path.push_back(Vector3f(1,1,0));
  path.push_back(Vector3f(1,1,0));
  path.push_back(Vector3f(1,1,0));
  path.push_back(Vector3f(1,1,0));
  AccelerometerSimulator simulator(path, 0.001);

  EXPECT_EQ(simulator.getDataFor(path.size() - 1), AccelerometerSimulator::GRAVITY);
}

// TEST_F(AccelerometerSimulatorTest, SometimesBazFalseIsTrue) {
//     Foo foo(m_bar);
//     // Have norf return true for once
//     EXPECT_CALL(m_bar,norf()).WillOnce(Return(true));
//     EXPECT_EQ(foo.baz(false), true);
// }

