file(GLOB SENSOR_SIMULATORS_SRC
  "*.h"
  "*.cpp"
)

add_library (sensor-simulators ${SENSOR_SIMULATORS_SRC})

target_link_libraries(
  sensor-simulators
)