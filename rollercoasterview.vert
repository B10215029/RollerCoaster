// Vertex shader for shadow map generation
#version 430 core
uniform mat4 MVPMatrix;
layout (location = 0) in vec3 position;
void main(void)
{
	gl_Position =MVPMatrix * vec4(position,1);
	//gl_Position = vec4(0,0,0,1);
}
