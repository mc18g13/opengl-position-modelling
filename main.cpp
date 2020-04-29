// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Grid.h"
#include "Cube.h"
#include "Orientation.h"
#include "Cylinder.h"

#include "PlotArea.h"
#include "TrackableObject.h"

#include "Camera.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/common.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include <cstdlib>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 1000.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

using namespace std;

GLFWwindow* InitWindow()
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

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

int main( void ) {
    GLFWwindow* window = InitWindow();
    if (!window)
        return -1;

    GLCall( glClearColor(1.0f, 1.0f, 1.0f, 1.0f) );
    GLCall( glEnable(GL_DEPTH_TEST) );
    GLCall( glDepthFunc(GL_LESS) );
    GLCall( glEnable(GL_BLEND) );
    GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );

    {
    	float screenWidth  = 960.0f;
    	float screenHeight = 540.0f;
    	float screenDepth  = 10*2000.0f;

    	float halfScreenWidth = screenWidth/2;
    	float halfScreenHeight = screenHeight/2;
    	float halfScreenDepth = screenDepth/2;

      Shader shader("src/gl-renderer/res/shaders/Basic.shader");
      shader.bind();

      double previousTime = glfwGetTime();
      int frameCount = 0;

      Renderer renderer;

      PlotArea plotArea(renderer);
      TrackableObject trackableObject(renderer);

    	mat4 View = mat4();
      mat4 sceneModel = mat4(1.0f);

      mat4 MVPOrientation = mat4(1.0f);
      mat4 MVPScene = mat4(1.0f);

      float abc = 0;
      do {

        processInput(window);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        abc += 0.6;
        
        vec3 positionView(0,abc, abc);

        //         View = glm::lookAt(
        //   positionView + vec3(150.f,150.f,600.f),
        //   positionView,
        //   glm::vec3(0.f,1.f,0.f)
        // );


        mat4 projection = glm::perspective(glm::radians(camera.getZoom()), (float) halfScreenWidth / (float)halfScreenHeight, 1.0f, 50000.0f);
        // glm::mat4 projection = glm::perspective(, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        // ourShader.setMat4("projection", projection);

        // camera/view transformation
        mat4 view = camera.getViewMatrix();
        // ourShader.setMat4("view", view);

        plotArea.setProjection(projection);
        trackableObject.setProjection(projection);
        plotArea.setView(view);
        trackableObject.setView(view);
        
        glEnable(GL_DEPTH_TEST);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

        renderer.Clear();

        glStencilMask(0x00);
        
        plotArea.setModel(sceneModel);
        plotArea.draw(shader);

        vec3 position(0,abc + (rand() % 20 - 20),abc + (rand() % 20 - 20));
        trackableObject.resetModel();
        trackableObject.setPosition(position);
        trackableObject.setOrientation(rotate(mat4(1.0f), glm::radians(abc), vec3(1, 0, 0)));
        trackableObject.draw(shader);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

        double currentTime = glfwGetTime();
        frameCount++;

        if ( currentTime - previousTime >= 1.0 ) {
            frameCount = 0;
            previousTime = currentTime;
        }

      } // Check if the ESC key was pressed or the window was closed
      while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0 );

    }

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
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


void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
  if (firstMouse) {
      lastX = xpos;
      lastY = ypos;
      firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

  lastX = xpos;
  lastY = ypos;

  camera.processMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  camera.processMouseScroll(yoffset);
}