#include <GLMathematics.h>
quat GLMathematics::rotationBetweenVectors(vec3 start, vec3 dest) {
  start = normalize(start);
  dest = normalize(dest);

  float cosTheta = dot(start, dest);
  vec3 rotationAxis;

  if (cosTheta < -1 + 0.001f) {
    // special case when vectors in opposite directions:
    // there is no "ideal" rotation axis
    // So guess one; any will do as long as it's perpendicular to start
    rotationAxis = cross(vec3(0.0f, 0.0f, 1.0f), start);
    if (length2(rotationAxis) < 0.01 ) // bad luck, they were parallel, try again!
      rotationAxis = cross(vec3(1.0f, 0.0f, 0.0f), start);

    rotationAxis = normalize(rotationAxis);
    return angleAxis(radians(180.0f), rotationAxis);
  }

  rotationAxis = cross(start, dest);

  float s = sqrt( (1+cosTheta)*2 );
  float invs = 1 / s;

  return quat(
    s * 0.5f,
    rotationAxis.x * invs,
    rotationAxis.y * invs,
    rotationAxis.z * invs
  );

}

// Like SLERP, but forbids rotation greater than maxAngle (in radians)
// In conjunction to LookAt, can make your characters
quat GLMathematics::rotateTowards(quat q1, quat q2, float maxAngle) {

  if( maxAngle < 0.001f ){
    // No rotation allowed. Prevent dividing by 0 later.
    return q1;
  }

  float cosTheta = dot(q1, q2);

  // q1 and q2 are already equal.
  // Force q2 just to be sure
  if(cosTheta > 0.9999f){
    return q2;
  }

  // Avoid taking the long path around the sphere
  if (cosTheta < 0){
    q1 = q1*-1.0f;
    cosTheta *= -1.0f;
  }

  float angle = acos(cosTheta);

  // If there is only a 2° difference, and we are allowed 5°,
  // then we arrived.
  if (angle < maxAngle){
    return q2;
  }

  // This is just like slerp(), but with a custom t
  float t = maxAngle / angle;
  angle = maxAngle;

  quat res = (sin((1.0f - t) * angle) * q1 + sin(t * angle) * q2) / sin(angle);
  res = normalize(res);
  return res;

}