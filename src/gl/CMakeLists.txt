file(GLOB GL_SRC
  "renderer/*.h"
  "renderer/*.cpp"
  "renderables/*.h"
  "renderables/*.cpp"
  "object-renderers/*.h"
  "object-renderers/*.cpp"
)

include_directories ("renderer")
include_directories ("renderables")
include_directories ("object-renderers")
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})

add_library (gl STATIC ${GL_SRC})

find_package(GLEW REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
pkg_search_module(GLFW REQUIRED glfw3)


link_libraries(${GLEW_LIBRARIES})
target_link_libraries( 
  gl
  GLEW
  OpenGL::OpenGL 
  ${GLFW_LIBRARIES}
  ${GLFW_STATIC_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(gl PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/renderer
  ${CMAKE_CURRENT_SOURCE_DIR}/renderables
  ${CMAKE_CURRENT_SOURCE_DIR}/object-renderers
  ${GLFW_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIRS}
)
