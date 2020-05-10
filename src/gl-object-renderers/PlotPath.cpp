#include "PlotPath.h"
#include "Cylinder.h"
#include "PositionHistory.h"

PlotPath::PlotPath(const Renderer& renderer) 
  : ObjectRenderer(renderer),
    m_positions() {

}

void PlotPath::addPosition(const vec3& position) { 
  bool notFirstPointAdded = m_positions.size() > 0;
  if (notFirstPointAdded) {
    vec3 lastPosition = m_positions.back();
    const float distanceFromLastPlottedLocationToPlot = 1.0f;
    if (glm::distance(position, lastPosition) > distanceFromLastPlottedLocationToPlot) {
      m_positions.push_back(position);
    }
  } else {
    m_positions.push_back(position);
  }

  const size_t MAX_POSITIONS_IN_HISTORY = 10000;
  if (m_positions.size() >= MAX_POSITIONS_IN_HISTORY) {
    m_positions.pop_front();
  }
}

void PlotPath::draw(Shader& shader) {

  shader.setUniformMat4f("u_MVP", getMVP());

  constexpr float RADIUS = 0.5;
  constexpr vec3 color = vec3(0.1f, 0.3f, 0.1f);

  for (size_t i = 0; i < m_positions.size() - 1; ++i) {
    vec3 olderPosition = m_positions.at(i);
    vec3 newerPosition = m_positions.at(i + 1);

    vec3 vectorToNewPosition = newerPosition - olderPosition;

    float length = distance(olderPosition, newerPosition);

    Cylinder nextLineSegment(vectorToNewPosition, olderPosition, color, length, RADIUS);
    m_renderer.draw(nextLineSegment, shader, GL_TRIANGLE_STRIP);
  }
}