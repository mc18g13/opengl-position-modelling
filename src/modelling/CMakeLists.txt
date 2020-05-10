file(GLOB MODELLING_SRC
  "*.h"
  "*.cpp"
)

add_subdirectory (sensor-simulators) 

add_library (modelling ${MODELLING_SRC})

target_link_libraries(
  modelling 
  sensor-simulators
  common
  Eigen3::Eigen
)