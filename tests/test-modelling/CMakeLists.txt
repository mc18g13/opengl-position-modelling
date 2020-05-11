file(GLOB SRCS 
  *.cpp
  *.h
)

ADD_EXECUTABLE(test-modelling ${SRCS})

TARGET_LINK_LIBRARIES(test-modelling
  modelling
  ${GTEST_LIBRARY}
  ${GTEST_MAIN_LIBRARY}
  ${GMOCK_LIBRARY}
  ${GMOCK_MAIN_LIBRARY}
)

include(GoogleTest)
gtest_discover_tests(test-modelling TEST_LIST targetList)

set_tests_properties(${targetList} PROPERTIES TIMEOUT 10)