#version 430
layout(location = 0) in vec3 vPosition;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void) {
	mat4 modelView = viewMatrix * modelMatrix;
	mat4 MVP = projectionMatrix * modelView;
	gl_Position = MVP * vec4(vPosition, 1);
}
