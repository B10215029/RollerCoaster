#version 430
//layout (binding = 1) uniform sampler2DShadow depth_texture;
layout (binding = 1) uniform sampler2D depth_texture;

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
//in vec3 pLightDirection;
in vec4 pShadowCoord;

out vec4 fragColor;

void main(void){
//	float f = textureProj(depth_texture, pShadowCoord);
//	float f = textureProj(depth_texture, vec4(0.5,0.5,0,1));
	float f=1;
//	if(texture2D(depth_texture, pShadowCoord.xy).r<pShadowCoord.z)
//	float f=texture2D(depth_texture, pShadowCoord.xy).a;
	vec3 ambient = Ka;
	vec3 diffuse = Kd;
	if(useTexture != -1)
		diffuse = texture2D(tex, pUV).rgb;
	diffuse = f*diffuse * max(dot(pNormal, normalize(lightDirection)), 0);
	vec3 halfv = normalize(normalize(lightDirection) + normalize(eyePosition-pPosition));
	vec3 specular = Ks * pow(max(dot(pNormal, halfv), 0), Ns);
	fragColor = vec4(ambient + diffuse + specular, 1);
	fragColor = texture2D(depth_texture, pShadowCoord.xy);
	//if(abs(pShadowCoord.x)<0.1 && abs(pShadowCoord.y)<0.1)
	//	fragColor = vec4(1,1,0,1);
	//fragColor = vec4(f,f,f,1);
	//fragColor = vec4(0,0,0,1);
	//fragColor.a = texture2D(depth_texture, gl_FragCoord.xy/1000);

	//fragColor = vec4(1);
}
