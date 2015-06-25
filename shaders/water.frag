#version 430
layout (binding = 0) uniform sampler2D tex;

in vec2 pUV;
out vec4 fragColor;

void main(void){
	fragColor = texture2D(tex, pUV);
	fragColor.a = 0.5;
}
