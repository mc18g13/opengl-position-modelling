#ifndef PLOT_PATH_H
#define PLOT_PATH_H

#include "ObjectRenderer.h"

#include <deque>

class PlotPath : public ObjectRenderer {
private:
  std::deque<vec3> m_positions;
public:
  PlotPath(const Renderer& renderer);
  virtual void draw(Shader& shader) override;
  void addPosition(const vec3& position);
};

#endif