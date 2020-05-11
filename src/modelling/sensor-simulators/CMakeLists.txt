file(GLOB SENSOR_SIMULATORS_SRC
  "*.h"
  "*.cpp"
)

include_directories(${PROJECT_SOURCE_DIR}/src/common)
add_library (sensor-simulators ${SENSOR_SIMULATORS_SRC})

target_link_libraries(
  sensor-simulators
)

target_include_directories(sensor-simulators PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)
