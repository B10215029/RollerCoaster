#version 430
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vUV;
layout(location = 2) in vec3 vNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 shadowMatrix;

out vec3 pPosition;
out vec2 pUV;
out vec3 pNormal;

void main(void) {
	mat4 modelView = viewMatrix * modelMatrix;
	mat4 MVP = projectionMatrix * modelView;
	//pPosition = (vec4(vPosition,1) * modelView).xyz;
	pPosition = vec3(modelMatrix * vec4(vPosition,1));
	pUV = vUV;
	//pNormal = normalize(mat3(modelMatrix) * vNormal);
	pNormal = normalize(mat3(modelMatrix) * vNormal);
	gl_Position = MVP * vec4(vPosition, 1);
}
