file(GLOB GL_OBJECT_RENDERERS_SRC
  "*.h"
  "*.cpp"
)

add_library (gl-object-renderers ${GL_OBJECT_RENDERERS_SRC})

target_link_libraries(gl-object-renderers gl-renderables)
target_link_libraries(gl-object-renderers gl-renderer)