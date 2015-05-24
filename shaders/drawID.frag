#version 430
uniform int ID;
out vec4 fragColor;

void main(void){
	fragColor = vec4(ID);
}
