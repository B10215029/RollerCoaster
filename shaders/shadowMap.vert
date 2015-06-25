// Vertex shader for shadow map generation
#version 430 core
uniform mat4 MMatrix;
uniform mat4 VPMatrix;
layout (location = 0) in vec3 position;
void main(void){
	gl_Position =VPMatrix * MMatrix * vec4(position,1);
	//gl_Position.z = -1;
	//gl_Position = vec4(0,0,0,1);
}
