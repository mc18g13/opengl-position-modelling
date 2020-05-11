set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14") 
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

find_package(Eigen3 REQUIRED)
find_package(Threads REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIR})

add_subdirectory(common)
add_subdirectory(gl) 
add_subdirectory(modelling)

add_executable(main main.cpp)

link_libraries(${GLEW_LIBRARIES})
target_link_libraries( 
  main 
  gl
  modelling
  pthread)



