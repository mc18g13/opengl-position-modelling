#ifndef GLMATHEMATICS_H_
#define GLMATHEMATICS_H_

#define GLM_ENABLE_EXPERIMENTAL

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

using namespace glm;

class GLMathematics {
public:
	static quat rotationBetweenVectors(vec3 start, vec3 dest);
	// Like SLERP, but forbids rotation greater than maxAngle (in radians)
	static quat rotateTowards(quat q1, quat q2, float maxAngle);
};

#endif 
