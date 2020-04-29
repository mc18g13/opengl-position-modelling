cmake_minimum_required(VERSION 3.10)
project(kalman-filter-3d-simulator C CXX)
set(CMAKE_BUILD_TYPE Debug)

# set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14") 

find_package(GLEW REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)

pkg_search_module(GLFW REQUIRED glfw3)

include_directories ("src/")
include_directories ("src/gl-renderables")
include_directories ("src/gl-renderer")
include_directories ("src/gl-object-renderers")

file(GLOB GL_RENDERABLES_SRC
  "src/gl-renderables/*.h"
  "src/gl-renderables/*.cpp"
)

add_library (gl-renderables STATIC ${GL_RENDERABLES_SRC})

file(GLOB GL_RENDERER_SRC
    "src/gl-renderer/*.h"
    "src/gl-renderer/*.cpp"
)

add_library (gl-renderer ${GL_RENDERER_SRC})
target_link_libraries(gl-renderer OpenGL::OpenGL)

include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})

add_subdirectory (src/gl-renderables) 
add_subdirectory (src/gl-renderer)
add_subdirectory (src/gl-object-renderers) 

add_executable (main main.cpp)

link_libraries(${GLEW_LIBRARIES})

# set(BOOST_LIBS date_time system)
# find_package(Boost COMPONENTS ${BOOST_LIBS} REQUIRED)
# target_link_libraries(main ${Boost_LIBRARIES})
find_package(Threads REQUIRED)
target_link_libraries(main ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries ( 
  main 
  gl-renderables 
  gl-renderer 
  gl-object-renderers
  GLEW 
  OpenGL::OpenGL 
  pthread 
  ${GLFW_LIBRARIES}
  ${GLFW_STATIC_LIBRARIES})



