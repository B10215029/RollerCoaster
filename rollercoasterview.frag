#version 430 core
//fragment shader
in vec4 outcolor;
out vec4 fragmentcolor; 

void main()
{
	fragmentcolor = outcolor; 
}
