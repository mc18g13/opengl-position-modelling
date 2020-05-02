#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 vertexColor;

uniform mat4 u_MVP;
out vec4 fragmentColor;
out vec4 positionSwitchYandZ;

void main()
{
  positionSwitchYandZ = vec4(position.x,position.z,position.y,position.w);
  gl_Position = u_MVP * positionSwitchYandZ;
  fragmentColor = vec4(vertexColor, 1.0f);
}

#shader fragment
#version 330 core

in vec4 fragmentColor;

void main()
{
  gl_FragColor = fragmentColor;
}
