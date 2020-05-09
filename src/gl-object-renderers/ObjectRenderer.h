#ifndef OBJECT_RENDERER_H
#define OBJECT_RENDERER_H

#include "Renderer.h"
#include "RenderableData.h"
#include "Renderable.h"
#include <memory>

class ObjectRenderer {
private:
  mat4 m_model;
  mat4 m_view;
  mat4 m_projection;

protected:
  Renderer m_renderer;

public:
  ObjectRenderer(const Renderer& renderer);
  virtual void draw(Shader& shader) = 0;

  void translateModel(const vec3& translation);
  void rotateModel(const float angleDegrees, const vec3& angleAxis);

  void setModel(const mat4& model);
  void setView(const mat4& view);
  void setProjection(const mat4& projection);

  const mat4& getModel();

  mat4 getMVP() const;

};

#endif