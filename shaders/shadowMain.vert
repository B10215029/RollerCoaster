#version 430
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vUV;
layout(location = 2) in vec3 vNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
//uniform vec3 lightPosition;
uniform mat4 shadowMatrix;

out vec3 pPosition;
out vec2 pUV;
out vec3 pNormal;
//out vec3 pLightDirection;
out vec4 pShadowCoord;

void main(void) {
	mat4 modelView = viewMatrix * modelMatrix;
	mat4 MVP = projectionMatrix * modelView;
	//vec4 vPosition4 = modelView * vec4(vPosition, 1);
	//vec3 vPosition3 = vPosition4.xyz / vPosition4.w;
	//pPosition = -vPosition3;
//	pPosition = (vec4(vPosition,1) * modelView).xyz;
	pPosition = (modelMatrix * vec4(vPosition,1)).xyz;
	pUV = vUV;
	//pNormal = normalize((vec4(vNormal,1) * modelView).xyz);
	pNormal = normalize(mat3(modelMatrix) * vNormal);
	//pLightDirection = normalize(lightPosition - vPosition3);
	pShadowCoord = shadowMatrix * (modelMatrix * vec4(vPosition,1));
	gl_Position = MVP * vec4(vPosition, 1);
}
