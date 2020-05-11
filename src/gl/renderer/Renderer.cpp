#include "Renderer.h"
#include <iostream>

void Renderer::clear() const
{
  GLCall( glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ) );
  GLCall( glClear( GL_STENCIL_BUFFER_BIT ) );
}

void Renderer::draw(const RenderableData& data, const Shader& shader, unsigned int geometryType) const
{
  shader.bind();
  data.bind();
  GLCall( glDrawElements(geometryType, data.getIndexCount(), GL_UNSIGNED_INT, nullptr) );
}

