﻿// Fragment shader for shadow map generation
#version 430 core
layout (location = 0) out vec4 color;
void main(void){
	color = vec4(1.0);
	//color = vec4(gl_FragCoord.z);
}
