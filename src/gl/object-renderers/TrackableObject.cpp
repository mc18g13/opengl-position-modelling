#include "TrackableObject.h"
#include "Cylinder.h"
#include "PositionHistory.h"

#include <glm/ext.hpp>

TrackableObject::TrackableObject(const Renderer& renderer) 
  : ObjectRenderer(renderer),
    m_trackableObject(nullptr),
    m_trackableObjectOutline(nullptr){

  const float LENGTH = 100.0f;
  const float RADIUS = 5.0f;
  Cylinder orientationXAxis(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), LENGTH, RADIUS);
  Cylinder orientationYAxis(vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), LENGTH, RADIUS);
  Cylinder orientationZAxis(vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), LENGTH, RADIUS);

  const float LENGTH_OUTLINE = LENGTH + 1;
  const float RADIUS_OUTLINE = RADIUS + 1;
  Cylinder orientationXAxisOutline(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f), LENGTH_OUTLINE, RADIUS_OUTLINE);
  Cylinder orientationYAxisOutline(vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f), LENGTH_OUTLINE, RADIUS_OUTLINE);
  Cylinder orientationZAxisOutline(vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f), LENGTH_OUTLINE, RADIUS_OUTLINE);

  Renderable orientationAxes = orientationXAxis + orientationYAxis + orientationZAxis;
  Renderable orienationAxesOutline = orientationXAxisOutline + orientationYAxisOutline + orientationZAxisOutline;

  m_trackableObject        = std::make_unique<RenderableData>(orientationAxes);
  m_trackableObjectOutline = std::make_unique<RenderableData>(orienationAxesOutline);

}

void TrackableObject::resetModel() {
  setModel(mat4(1.0f));
}

void TrackableObject::setPosition(const vec3& position) { 
  translateModel(position);
}

void TrackableObject::setOrientation(const quat& orientation) {
  rotateModel(angle(orientation), axis(orientation));
}

void TrackableObject::setOrientation(const float angleDegrees, const vec3& angleAxis) {
  rotateModel(angleDegrees, angleAxis);
}

void TrackableObject::draw(Shader& shader) {

  shader.setUniformMat4f("u_MVP", getMVP());

  glDepthMask(false);
  m_renderer.draw(*m_trackableObjectOutline, shader, GL_TRIANGLE_STRIP);
  glDepthMask(true);
  m_renderer.draw(*m_trackableObject, shader, GL_TRIANGLE_STRIP);

}