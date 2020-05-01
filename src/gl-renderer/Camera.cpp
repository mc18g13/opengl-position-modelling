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
    m_front(PERPENDICULAR_TO_SCREEN), 
    m_movementSpeed(SPEED), 
    m_mouseSensitivity(SENSITIVITY), 
    m_zoom(ZOOM)
{
  m_rotationFromZeroEulersAtPositionToOrigin = GLMathematics::rotationBetweenVectors(m_front, -position);
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
    m_position + m_front, 
    m_up);
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime) {
  float velocity = m_movementSpeed * deltaTime;
  if (direction == FORWARD)
    m_position += m_front * velocity;
  if (direction == BACKWARD)
    m_position -= m_front * velocity;
  if (direction == LEFT)
    m_position -= m_right * velocity;
  if (direction == RIGHT)
    m_position += m_right * velocity;

  printVec(m_position);
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

  glm::vec3 euler = glm::eulerAngles(m_rotationFromZeroEulersAtPositionToOrigin);

  float pitchOffset = euler.x * 180 / M_PI;
  float yawOffset   = euler.y * 180 / M_PI;

  float pitchWithOffset = m_pitch + pitchOffset;
  float yawWithOffset   = m_yaw   - yawOffset;


  m_front.x = cos(glm::radians(yawWithOffset)) * cos(glm::radians(pitchWithOffset));
  m_front.y = sin(glm::radians(pitchWithOffset));
  m_front.z = sin(glm::radians(yawWithOffset)) * cos(glm::radians(pitchWithOffset));

  m_front   = glm::normalize(m_front);

  m_right = glm::normalize(glm::cross(m_front, m_worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
  m_up    = glm::normalize(glm::cross(m_right, m_front));

}

void Camera::printVec(glm::vec3& vector) {
  std::cout << vector.x << " "
            << vector.y << " "
            << vector.z << std::endl;
}
