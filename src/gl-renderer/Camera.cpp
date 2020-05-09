#include "Camera.h"

#include <iostream>
#include "GLMathematics.h"
#include "math.h"

namespace {
  vec3 PERPENDICULAR_TO_SCREEN(0.0f, 0.0f, -1.0f);
}

Camera::Camera(
  glm::vec3 position, glm::vec3 up,
  float yaw, float pitch) : 
    m_directionCameraIsFacing(PERPENDICULAR_TO_SCREEN), 
    m_movementSpeed(SPEED), 
    m_mouseSensitivity(SENSITIVITY), 
    m_zoom(ZOOM)
{
  m_position         = position;
  m_worldUp          = up;
  m_yaw              = yaw;
  m_pitch            = pitch;

  updateCameraVectors();
}

const float Camera::getZoom() {
  return m_zoom;
}

glm::mat4 Camera::getViewMatrix() {
  return glm::lookAt(
    m_position, 
    m_position + m_directionCameraIsFacing, 
    m_up);
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime) {
  float velocity = m_movementSpeed * deltaTime;
  vec3 changeInXZPlane(m_directionCameraIsFacing.x,0.0f,m_directionCameraIsFacing.z);
  changeInXZPlane = glm::normalize(changeInXZPlane);
  if (direction == FORWARD)
    m_position += changeInXZPlane * velocity;
  if (direction == BACKWARD)
    m_position -= changeInXZPlane * velocity;
  if (direction == LEFT)
    m_position += m_right * velocity;
  if (direction == RIGHT)
    m_position -= m_right * velocity;
}


void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
  xoffset *= m_mouseSensitivity;
  yoffset *= m_mouseSensitivity;

  m_yaw   += xoffset;
  m_pitch += yoffset;

  if (constrainPitch)
  {
    constexpr float MAX_FOR_PITCH = 89.0f;
    if (m_pitch > MAX_FOR_PITCH)
      m_pitch = MAX_FOR_PITCH;
    if (m_pitch < -MAX_FOR_PITCH)
      m_pitch = -MAX_FOR_PITCH;
  }

  updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset) {
  constexpr float ZOOM_MAX = 500;
  if (m_zoom >= 1.0f && m_zoom <= ZOOM_MAX)
    m_zoom += yoffset;
  if (m_zoom <= 1.0f)
    m_zoom = 1.0f;
  if (m_zoom >= ZOOM_MAX)
    m_zoom = ZOOM_MAX;
}

void Camera::updateCameraVectors() {  

  float pitchWithOffset = m_pitch;
  float yawWithOffset   = m_yaw  ;
  
  m_directionCameraIsFacing.x = cos(glm::radians(yawWithOffset)) * cos(glm::radians(pitchWithOffset));
  m_directionCameraIsFacing.y = sin(glm::radians(pitchWithOffset));
  m_directionCameraIsFacing.z = sin(glm::radians(yawWithOffset)) * cos(glm::radians(pitchWithOffset));

  m_directionCameraIsFacing   = glm::normalize(m_directionCameraIsFacing);

  m_right = glm::normalize(glm::cross(m_directionCameraIsFacing, m_worldUp));
  m_up    = glm::normalize(glm::cross(m_right, m_directionCameraIsFacing));

}

void Camera::printVec(glm::vec3& vector, const char* name) {
  std::cout << name << " " 
            << vector.x << " "
            << vector.y << " "
            << vector.z << std::endl << std::endl;
}
