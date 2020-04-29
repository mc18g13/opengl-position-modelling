#include "ObjectRenderer.h"

ObjectRenderer::ObjectRenderer(const Renderer& renderer) 
  : m_renderer(renderer) {

}

void ObjectRenderer::setModel(const mat4& model) {
  m_model = model;
}

void ObjectRenderer::setView(const mat4& view) {
  m_view = view;
}

void ObjectRenderer::setProjection(const mat4& projection) {
  m_projection = projection;
}

const mat4& ObjectRenderer::getModel() {
  return m_model;
}

mat4 ObjectRenderer::getMVP() const {
  return m_projection * m_view * m_model;
}