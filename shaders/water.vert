#version 430
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vUV;

uniform mat4 MVPMatrix;
uniform float time;
out vec2 pUV;

void main(void) {
	vec4 pos = vec4(vPosition*10, 1);
	pUV = vUV+vec2(sin(time+pos.x/50.0+1.57)*0.2,cos(time+pos.x/50.0+1.57)*0.2);
	pos.y+=sin(time+pos.x/50.0)*10+sin(time*5)-300;
	gl_Position = MVPMatrix * pos;
}
