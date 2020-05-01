#include "TrackableObject.h"
#include "Cylinder.h"
#include "PositionHistory.h"

TrackableObject::TrackableObject(const Renderer& renderer) 
  : ObjectRenderer(renderer) {

  const float LENGTH = 100.0f;
  const float RADIUS = 5.0f;
  Cylinder orientationXAxis(vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), LENGTH, RADIUS);
  Cylinder orientationYAxis(vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), LENGTH, RADIUS);
  Cylinder orientationZAxis(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), LENGTH, RADIUS);

  Cylinder orientationXAxisOutline(vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f), LENGTH + 1, RADIUS + 1);
  Cylinder orientationYAxisOutline(vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f), LENGTH + 1, RADIUS + 1);
  Cylinder orientationZAxisOutline(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f), LENGTH + 1, RADIUS + 1);

  Renderable orientationAxes = orientationXAxis + orientationYAxis + orientationZAxis;
  Renderable orienationAxesOutline = orientationXAxisOutline + orientationYAxisOutline + orientationZAxisOutline;

  m_trackableObject        = std::make_unique<RenderableData>(orientationAxes);
  m_trackableObjectOutline = std::make_unique<RenderableData>(orienationAxesOutline);

}

void TrackableObject::resetModel() {
  this->setModel(mat4(1.0f));
}

void TrackableObject::setPosition(const vec3& position) { 
  setModel(translate(getModel(), position));
  if (m_positions.size() > 0) {
    vec3 lastPosition = m_positions.back();
    const float distanceFromLastPlottedLocationToPlot = 50.0f;
    if (glm::distance(position, lastPosition) > distanceFromLastPlottedLocationToPlot) {
      m_positions.push_back(position);
    }
  } 
  else
  {
    m_positions.push_back(position);
  }

  const size_t MAX_POSITIONS_IN_HISTORY = 100;
  if (m_positions.size() >= MAX_POSITIONS_IN_HISTORY) {
    m_positions.pop_front();
  }

  const float RADIUS = 20;
  const vec3 color = vec3(0.0f, 0.0f, 0.0f);

  std::unique_ptr<Renderable> path;
 
  for (int i = 0; i < m_positions.size() - 1; ++i) {
    vec3 olderPosition = m_positions.at(i);
    vec3 newerPosition = m_positions.at(i + 1);

    vec3 vectorToNewPosition = newerPosition - olderPosition;

    float length = distance(olderPosition, newerPosition);
    if (i == 0) {
      Cylinder startPath(vectorToNewPosition, olderPosition, color, length, RADIUS);
      path = std::make_unique<Renderable>(startPath);
    } else {
      *path += Cylinder(vectorToNewPosition, olderPosition, color, length, RADIUS);
    }

  }

  if (path) {
    m_historyData = std::make_unique<RenderableData>(*path);
  }
  
}

void TrackableObject::setOrientation(const quat& orientation) {
  mat4 rotation = mat4_cast(orientation);
  setModel(getModel());
}

void TrackableObject::setOrientation(const mat4& orientation) {
  setModel(getModel() * orientation);
}

void TrackableObject::draw(Shader& shader) {

  shader.SetUniformMat4f("u_MVP", getMVP());

  glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
  glStencilMask(0x00); 
  glDisable(GL_DEPTH_TEST);
  
  m_renderer.draw(*m_trackableObjectOutline, shader, GL_TRIANGLE_STRIP);

  glEnable(GL_DEPTH_TEST);
  glStencilMask(0xFF);
  glStencilFunc(GL_ALWAYS, 1, 0xFF);   

  m_renderer.draw(*m_trackableObject, shader, GL_TRIANGLE_STRIP);
  
  glStencilMask(0x00);

  // Cylinder orientationXAxisOutline(vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f), LENGTH + 1, RADIUS + 1);
  // history.printIndices();

  if (m_historyData) {
    setModel(mat4(1.0f));
    shader.SetUniformMat4f("u_MVP", getMVP());
    m_renderer.draw(*m_historyData, shader, GL_TRIANGLE_STRIP);
  }
  
}

void TrackableObject::setAxisScale(const mat4& scale) {
  setModel(getModel() * scale);
}