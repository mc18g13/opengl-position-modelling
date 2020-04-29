#ifndef CAMERA_H
#define CAMERA_H

// #include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  200.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;
#include <iostream>
class Camera {
private:
  glm::vec3 m_position;
  glm::vec3 m_front;
  glm::vec3 m_up;
  glm::vec3 m_right;
  glm::vec3 m_worldUp;

  float m_yaw;
  float m_pitch;

  float m_movementSpeed;
  float m_mouseSensitivity;
  float m_zoom;

public:

  Camera(
    glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f), 
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
    float yaw = YAW, float pitch = PITCH) : 
      m_front(glm::vec3(0.0f, -1.0f, 0.0f)), 
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

  Camera(
    float posX, float posY, float posZ, 
    float upX, float upY, float upZ, 
    float yaw, float pitch) : 
      m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_movementSpeed(SPEED), 
      m_mouseSensitivity(SENSITIVITY), m_zoom(ZOOM) {
    m_position = glm::vec3(posX, posY, posZ);
    m_worldUp = glm::vec3(upX, upY, upZ);
    m_yaw = yaw;
    m_pitch = pitch;
    updateCameraVectors();
  }

  const float getZoom() {
    return m_zoom;
  }

  // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
  glm::mat4 getViewMatrix() {
    return glm::lookAt(m_position + vec3(150.f,150.f,600.f), m_position + m_front, m_up);

        // // View = 
        // return glm::lookAt(
        //   m_position + m_front,
        //   m_position,
        //   m_up
        // );

        //         View = glm::lookAt(
        //   positionView ,
        //   positionView,
        //   glm::vec3(0.f,1.f,0.f)
        // );


  }

  void processKeyboard(Camera_Movement direction, float deltaTime) {
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


  void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
    xoffset *= m_mouseSensitivity;
    yoffset *= m_mouseSensitivity;

    m_yaw   += xoffset;
    m_pitch += yoffset;

    std::cout << "m_yaw " << m_yaw << std::endl;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
      if (m_pitch > 89.0f)
        m_pitch = 89.0f;
      if (m_pitch < -89.0f)
        m_pitch = -89.0f;
    }

    // Update m_front, m_right and m_up Vectors using the updated Euler angles
    updateCameraVectors();
  }

  // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
  void processMouseScroll(float yoffset) {
    if (m_zoom >= 1.0f && m_zoom <= 45.0f)
      m_zoom -= yoffset;
    if (m_zoom <= 1.0f)
      m_zoom = 1.0f;
    if (m_zoom >= 45.0f)
      m_zoom = 45.0f;
  }

private:
  // Calculates the m_front vector from the Camera's (updated) Euler Angles
  void updateCameraVectors() {
    // Calculate the new m_front vector
    // glm::vec3 m_front;
    m_front.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
    m_front.z = sin(glm::radians(m_yaw));
    m_front.x = sin(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));

    // m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    // m_front.z = sin(glm::radians(m_pitch));
    // m_front.x = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    m_front   = glm::normalize(m_front);
    // Also re-calculate the m_right and m_up vector
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    m_up    = glm::normalize(glm::cross(m_right, m_front));
  }
};
#endif