#ifndef PLOT_AREA_H
#define PLOT_AREA_H

#include "ObjectRenderer.h"

class PlotArea : public ObjectRenderer {
private:
  std::unique_ptr<RenderableData> m_grid;
  std::unique_ptr<RenderableData> m_axis;

public:
  PlotArea(const Renderer& renderer);
  virtual void draw(Shader& shader) override;

};

#endif