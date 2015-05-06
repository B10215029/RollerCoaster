#version 430
struct MaterialInfo{
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float Ns;
};

//layout (binding = 0) uniform sampler2DShadow shadow_tex;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float Ns;
uniform vec3 lightPosition;
uniform vec3 eyePosition;

in vec3 pPosition;
//in vec2 pUV;
in vec3 pNormal;
//in vec3 pLightDirection;
//in vec4 pShadowCoord;

out vec4 fragColor;

void main(void){
	vec3 ambient = Ka;
	vec3 diffuse = Kd * max(dot(pNormal, normalize(lightPosition-pPosition)), 0);
	vec3 halfv = normalize(normalize(lightPosition-pPosition) + normalize(eyePosition-pPosition));
	vec3 specular = Ks * pow(max(dot(pNormal, halfv), 0), Ns);
	fragColor = vec4(ambient + diffuse + specular, 1);
}
