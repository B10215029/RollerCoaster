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

//in vec3 vVaryingNormal;
//in vec3 vVaryingLightDir;
//in vec2 UV;
//in vec3 V;
//in vec4 shadow_coord;
//vec4 ambientColor = vec4(0.1,0.1,0.1,1);
//vec4 diffuseColor = vec4(0.8,0.8,0.8,1);
//vec4 specularColor = vec4(1,1,1,1);
//float Shininess = 50.0;

void main(void){
	vec3 ambient = Ka;
	vec3 diffuse = Kd * max(dot(pNormal, normalize(lightPosition-pPosition)), 0);
	vec3 halfv = normalize(normalize(lightPosition-pPosition) + normalize(eyePosition-pPosition));
	vec3 specular = Ks * pow(max(dot(pNormal, halfv), 0), Ns);
	fragColor = vec4(ambient + diffuse + specular, 1);

//	float diff = max(0.0, dot(normalize(vVaryingNormal),normalize(vVaryingLightDir)))*1.2;
//	if(displayMode/2%2==1)//toon
//		diff = floor(diff * float(3)) / float(3)*5./3.;
//	if(displayMode/64%2==1)//Solarization
//		diff = 1-diff;
//	vec4 diffuse = diff * diffuseColor * vec4(Material.Kd,1);
//	vec3 vReflection = normalize(reflect(-normalize(vVaryingLightDir),normalize(vVaryingNormal)));
//	float spec = max(0.0, dot(normalize(vVaryingNormal), vReflection));
//	spec = pow(spec, Shininess);
//	vec4 specular = spec * specularColor * vec4(Material.Ks,1);
//	if(displayMode/256%2==1){//Spot
//		specular = vec4(0,0,0,1);
//		float lightDistance = length(vLightPosition-V);
//		float attenuation = 1.0f /(0.1 + 0.0 * lightDistance+ 0.0 * lightDistance * lightDistance);
//		float spotCos = dot(normalize(vVaryingLightDir),normalize(vLightPosition));
//		float spotLen = dot(normalize(vVaryingLightDir),vLightPosition);
//		if(spotCos<0.98)
//			attenuation = 0;
//		else
//			attenuation *= pow(spotLen,-1.0f);
//		//float diffuse = max(0.0, dot(normalize(vVaryingNormal),normalize(vVaryingLightDir)));
//		diffuse *= attenuation;
//		/*
//		float lightDistance = length(vLightPosition-V);
//		float attenuation = 1.0f /(0.1 + 0.0 * lightDistance+ 0.0 * lightDistance * lightDistance);
//	//	vec3 halfVector = normalize(normalize(vVaryingLightDir)+normalize(vec3(0,0,-1)));
//		float spotCos = dot(normalize(vVaryingLightDir),normalize(vLightPosition));
//		float spotLen = dot(normalize(vVaryingLightDir),vLightPosition);
//		if(spotCos<0.98)
//			attenuation = 0;
//		else
//			attenuation *= pow(spotLen,-1.0f);
//		float diffuse = max(0.0, dot(normalize(vVaryingNormal),normalize(vVaryingLightDir)));
//	//	float specular = max(0.0, dot(normalize(vVaryingNormal),halfVector));
//		//float specular = max(0.0, dot(normalize(vVaryingNormal),normalize(reflect(-normalize(vVaryingLightDir),normalize(vVaryingNormal)))));
//	//	specular = pow(specular, Shininess) * 5.0f;
//		vec3 scatteredLight = ambientColor.rgb + Material.Kd * diffuse * attenuation;
//	//	vec3 reflectedLight = Material.Ks * specular * attenuation;
//	//	vec3 rgb = min(scatteredLight + reflectedLight,vec3(1.0));
//		vFragColor = vec4(scatteredLight, 1);
//		*/
//	}
//	vFragColor = diffuse + specular + ambientColor;
//	if(displayMode/128%2==1){//Gold
//		diffuse = diff * diffuseColor * vec4(0.875164,0.760648,0.322648,1);
//		spec = max(0.0, dot(normalize(vVaryingNormal), vReflection));
//		specular = pow(spec, 128) * specularColor * vec4(0.9628281,0.8555802,0.5366065,1);
//		vFragColor = diffuse + specular + vec4(0.24725,0.1995,0.0745,1);
//	}
//	if(displayMode/4%2==1)//Shadow
//		vFragColor = textureProj(shadow_tex, shadow_coord) * vec4(diffuse + specular) + ambientColor;
//	if(displayMode/32%2==1)//Negative
//		vFragColor = vec4(1-vFragColor.x, 1-vFragColor.y, 1-vFragColor.z, vFragColor.w);
//	if(displayMode/8%2==1){//Gray
//		float gray = 0.2126 * vFragColor.r + 0.7152 * vFragColor.g + 0.0722 * vFragColor.b;
//		vFragColor = vec4(gray, gray, gray, vFragColor.w);
//	}
//	if(displayMode/16%2==1){//black&white
//		float gray = 0.2126 * vFragColor.r + 0.7152 * vFragColor.g + 0.0722 * vFragColor.b;
//		gray = floor(gray * float(2));
//		vFragColor = vec4(gray, gray, gray, vFragColor.w);
//	}
}
