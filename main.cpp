// Include GLEW
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>


#include <iostream>
#include <vector>
#include <cstdlib>

#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "PlotArea.h"
#include "PlotPath.h"
#include "TrackableObject.h"
#include "Camera.h"
#include "Model.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const glm::vec3 STARTING_CAMERA_LOCATION(1000.f,1000.f,1000.f);

Camera camera(STARTING_CAMERA_LOCATION);
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

using namespace std;

GLFWwindow* initWindow()
{
    // Initialise GLFW
    if( !glfwInit() ) {
      fprintf( stderr, "Failed to initialize GLFW\n" );
      getchar();
      return nullptr;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow(960 * 2 , 540 * 2, "OpenGL-Test", NULL, NULL);
    if( window == NULL ) {
      fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
      getchar();
      glfwTerminate();
      return nullptr;
    }

    glfwMakeContextCurrent(window);

    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);

    // tell GLFW to capture our mouse
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
      fprintf(stderr, "Failed to initialize GLEW\n");
      getchar();
      glfwTerminate();
      return nullptr;
    }

    std::cout << "Using GL Version: " << glGetString(GL_VERSION) << std::endl;

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    return window;
}

vec3 stateSpaceToGraphicSpace(Eigen::Vector3f& state) {
  return vec3(state[1], state[2], state[0]);
}

int main( void ) {
    GLFWwindow* window = initWindow();
    if (!window)
        return -1;

    GLCall( glClearColor(1.0f, 1.0f, 1.0f, 1.0f) );
    GLCall( glEnable(GL_DEPTH_TEST) );
    GLCall( glDepthFunc(GL_LESS) );
    GLCall( glEnable(GL_BLEND) );
    GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );

    {
    	constexpr float SCREEN_WIDTH  = 960.0f;
    	constexpr float SCREEN_HEIGHT = 540.0f;

    	constexpr float HALF_SCREEN_WIDTH = SCREEN_WIDTH/2;
    	constexpr float HALF_SCREEN_HEIGHT = SCREEN_HEIGHT/2;

      constexpr float PLOTTING_SCALE  = 400;
      constexpr float PLOTTING_WIDTH  = PLOTTING_SCALE * HALF_SCREEN_WIDTH;
    	constexpr float PLOTTING_HEIGHT = PLOTTING_SCALE * HALF_SCREEN_HEIGHT;
      constexpr float PLOTTING_DEPTH  = 10000.0f;

      Shader shader("src/gl-renderer/res/shaders/Basic.shader");
      shader.bind();

      double previousTime = glfwGetTime();
      int frameCount = 0;

      Renderer renderer;

      PlotArea plotArea(renderer);
      TrackableObject trackableObject(renderer);
      PlotPath objectPath(renderer);

      mat4 sceneModel = mat4(1.0f);

      Model stateModel;

      float abc = 0;
      do {

        processInput(window);

        // while (glfwGetTime() - lastFrame < 0.2);
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        abc += 1;
        // mat4 projection = glm::perspective(glm::radians(camera.getZoom()), (float) HALF_SCREEN_DEPTH / (float)HALF_SCREEN_HEIGHT, 1.0f, 50000.0f);

        float zoom = camera.getZoom();
        mat4 projection = glm::ortho(
          -PLOTTING_WIDTH/zoom, PLOTTING_WIDTH/zoom, 
          -PLOTTING_HEIGHT/zoom, PLOTTING_HEIGHT/zoom, 
          -PLOTTING_DEPTH * 1000/zoom, PLOTTING_DEPTH* 1000/zoom);

        plotArea.setProjection(projection);
        trackableObject.setProjection(projection);
        objectPath.setProjection(projection);
        
        mat4 view = camera.getViewMatrix();
        plotArea.setView(view);
        trackableObject.setView(view);
        objectPath.setView(view);

        glEnable(GL_DEPTH_TEST);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

        renderer.clear();

        glStencilMask(0x00);
        
        plotArea.setModel(sceneModel);
        plotArea.draw(shader);

        std::shared_future<Eigen::Vector3f> futurePosition = stateModel.getPosition();

        if (futurePosition.wait_for(std::chrono::milliseconds(5)) != std::future_status::timeout) {
          Eigen::Vector3f position = futurePosition.get();
          glm::vec3 positionDrawable = stateSpaceToGraphicSpace(position);

          // Eigen::IOFormat cleanFmt(4, 0, ", ", " ", "[", "]");
          // std::cout << position.format(cleanFmt) << std::endl;

          trackableObject.resetModel();
          trackableObject.setPosition(positionDrawable);
          trackableObject.setOrientation(abc, vec3(1, 0, 0));

          objectPath.addPosition(positionDrawable);
        }

        trackableObject.draw(shader);

        objectPath.setModel(sceneModel);
        objectPath.draw(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();

        double currentTime = glfwGetTime();
        frameCount++;

        if ( currentTime - previousTime >= 1.0 ) {
          frameCount = 0;
          previousTime = currentTime;
        }

      } while( 
        glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0 
      );

      stateModel.stop();
    }

    glfwTerminate();


 
    return 0;
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.processKeyboard(FORWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.processKeyboard(BACKWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.processKeyboard(LEFT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.processKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width and 
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {

  int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
  if (state == GLFW_PRESS) {

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    camera.processMouseMovement(xoffset, yoffset);
  }

  lastX = xpos;
  lastY = ypos;
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
  camera.processMouseScroll(yoffset);
}