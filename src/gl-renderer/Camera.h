#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
    float yaw = YAW, float pitch = PITCH);

  Camera(
    float posX, float posY, float posZ, 
    float upX, float upY, float upZ, 
    float yaw, float pitch);

  const float getZoom();

  // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
  glm::mat4 getViewMatrix();

  void processKeyboard(Camera_Movement direction, float deltaTime);

  void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

  // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
  void processMouseScroll(float yoffset);

private:
  // Calculates the m_front vector from the Camera's (updated) Euler Angles
  void updateCameraVectors();
};
#endif