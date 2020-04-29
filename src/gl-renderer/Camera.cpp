#include "Camera.h"

#include <iostream>

namespace {
  const glm::vec3 STARTING_CAMERA_LOCATION(1500.f,1500.f,2000.f);
}

Camera::Camera(
  glm::vec3 m_position, glm::vec3 up,
  float yaw, float pitch) : 
    m_front(glm::vec3(0.0f, 0.0f, 0.0f)), 
    m_movementSpeed(SPEED), 
    m_mouseSensitivity(SENSITIVITY), 
    m_zoom(ZOOM)
{
  m_position = m_position;
  m_worldUp = up;
  m_yaw = yaw;
  m_pitch = pitch;
  updateCameraVectors();
}

Camera::Camera(
  float posX, float posY, float posZ, 
  float upX, float upY, float upZ, 
  float yaw, float pitch) : 
    m_front(glm::vec3(0.0f, 0.0f, 0.0f)), m_movementSpeed(SPEED), 
    m_mouseSensitivity(SENSITIVITY), m_zoom(ZOOM) {
  m_position = glm::vec3(posX, posY, posZ);
  m_worldUp = glm::vec3(upX, upY, upZ);
  m_yaw = yaw;
  m_pitch = pitch;
  updateCameraVectors();
}

const float Camera::getZoom() {
  return m_zoom;
}

glm::mat4 Camera::getViewMatrix() {
  return glm::lookAt(
    m_position + STARTING_CAMERA_LOCATION, 
    m_position + STARTING_CAMERA_LOCATION + m_front, 
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
  if (m_zoom >= 1.0f && m_zoom <= 45.0f)
    m_zoom -= yoffset;
  if (m_zoom <= 1.0f)
    m_zoom = 1.0f;
  if (m_zoom >= 45.0f)
    m_zoom = 45.0f;
}

void Camera::updateCameraVectors() {
  // Calculate the new m_front vector
  m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  m_front.y = sin(glm::radians(m_pitch));
  m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

  m_front   = glm::normalize(m_front);
  // Also re-calculate the m_right and m_up vector
  m_right = glm::normalize(glm::cross(m_front, m_worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
  m_up    = glm::normalize(glm::cross(m_right, m_front));
}
