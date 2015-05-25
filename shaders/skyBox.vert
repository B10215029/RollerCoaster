#version 430
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vUV;

uniform mat4 MVPMatrix;
out vec2 pUV;

void main(void) {
	pUV = vUV;
	gl_Position = MVPMatrix * vec4(vPosition, 1);
//	gl_Position = vec4(vPosition/1000, 1);
}
