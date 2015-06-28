#version 430
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float Ns;
uniform vec3 lightDirection;
uniform vec3 eyePosition;
uniform int useTexture;
layout (binding = 0) uniform sampler2D tex;

in vec3 pPosition;
in vec2 pUV;
in vec3 pNormal;
out vec4 fragColor;

void main(void){
	vec3 ambient = Ka;
	vec4 texcolor = vec4(Kd, 1);
	if(useTexture != -1)
		texcolor = texture2D(tex, pUV);
	vec3 diffuse = texcolor.rgb * max(dot(normalize(pNormal), normalize(lightDirection)), 0);
	vec3 halfv = normalize(normalize(lightDirection) + normalize(eyePosition-pPosition));
	vec3 specular = Ks * pow(max(dot(pNormal, halfv), 0), Ns);
	fragColor = vec4(ambient + diffuse + specular, texcolor.a);
}
