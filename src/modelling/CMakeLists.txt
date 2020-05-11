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

target_include_directories(modelling PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)
