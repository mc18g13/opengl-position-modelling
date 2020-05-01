#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

enum Camera_Movement {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  500.0f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  250.0f;


class Camera {
private:
  glm::quat m_rotationFromZeroEulersAtPositionToOrigin;
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
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
    float yaw = YAW, float pitch = PITCH);

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
  void printVec(glm::vec3& vector);
};
#endif