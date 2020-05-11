#include "gtest/gtest.h"
#include "mockbar.h"

class AccelerometerSimulatorTest : public ::testing::Test {

protected:

  AccelerometerSimulatorTest();
  virtual ~AccelerometerSimulatorTest();

  virtual void SetUp() override;

  virtual void TearDown() override;

};
