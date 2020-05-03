file(GLOB MODELLING_SRC
  "*.h"
  "*.cpp"
)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
add_library (modelling ${MODELLING_SRC})

target_link_libraries(
  modelling 
  common
  Eigen3::Eigen
)