#pragma once

#include <GL/glew.h>

#include "Debug.h"
#include "RenderableData.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
public:
  void clear() const;
  void draw(const RenderableData& object, const Shader& shader, unsigned int geometryType) const;
};
