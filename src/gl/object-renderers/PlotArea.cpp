#include "PlotArea.h"

#include "Grid.h"
#include "Cylinder.h"


PlotArea::PlotArea(const Renderer& renderer) 
  : ObjectRenderer(renderer) {

  const float LENGTH = 1000.0f;
  const float RADIUS = 2.0f;

  Grid grid(LENGTH, LENGTH/10);
  Cylinder xAxis(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), LENGTH, RADIUS);
  Cylinder yAxis(vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), LENGTH, RADIUS);
  Cylinder zAxis(vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), LENGTH, RADIUS);

  Renderable axis = xAxis + yAxis + zAxis;

  m_axis = std::make_unique<RenderableData>(axis);
  m_grid = std::make_unique<RenderableData>(grid);

}

void PlotArea::draw(Shader& shader) {
  shader.setUniformMat4f("u_MVP", getMVP());
  m_renderer.draw(*m_axis, shader, GL_TRIANGLE_STRIP);
  m_renderer.draw(*m_grid, shader, GL_LINES);
}
