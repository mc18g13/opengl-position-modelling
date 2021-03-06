#ifndef TRACKABLE_OBJECT_H
#define TRACKABLE_OBJECT_H

#include "ObjectRenderer.h"

#include <deque>

class TrackableObject : public ObjectRenderer {
private:
  std::unique_ptr<RenderableData> m_trackableObject;
  std::unique_ptr<RenderableData> m_trackableObjectOutline;
  
public:
  TrackableObject(const Renderer& renderer);
  virtual void draw(Shader& shader) override;

  void resetModel();
  void setPosition(const vec3& position);
  void setOrientation(const quat& orientation);
  void setOrientation(const float angleDegrees, const vec3& angleAxis);
};

#endif