#version 430 core
//vertex shader
uniform mat4 offsetMat;
out vec4 outcolor;

float rand(vec2 n){
  return fract(sin(dot(n.xy, vec2(12.9898, 78.233)))* 43758.5453);
}
void main(){
	vec4 vertexs[6]=vec4[](
		vec4(0,		0.866,	0.5,1),
		vec4(-0.25,	0.433,	0.5,1),
		vec4(0.25,	0.433,	0.5,1),
		vec4(0.25,	0.433,	0.5,1),
		vec4(-0.25,	0.433,	0.5,1),
		vec4(0,		0,		0.5,1)
	);
	vec4 offsets[6]=vec4[](
		vec4(1,		0		,0,		1		),
		vec4(0.5,	0.866,	-0.866,	0.5		),
		vec4(-0.5,	0.866,	-0.866,	-0.5	),
		vec4(-1,	0,		0,		-1		),
		vec4(-0.5,	-0.866,	0.866,	-0.5	),
		vec4(0.5,	-0.866,	0.866,	0.5		)
	);
	vec4 colors[6]=vec4[](
		vec4(1,0,0,1),
		vec4(1,1,0,1),
		vec4(0,1,0,1),
		vec4(0,1,1,1),
		vec4(0,0,1,1),
		vec4(1,0,1,1)
	);
	mat4 ofs = mat4(mat2(offsets[gl_InstanceID][0],offsets[gl_InstanceID][1],offsets[gl_InstanceID][2],offsets[gl_InstanceID][3]));
	gl_Position = vertexs[gl_VertexID]*ofs*offsetMat;
	if(gl_VertexID<3)
		outcolor = colors[gl_InstanceID];
	else{
		vec4 of = (colors[gl_InstanceID]+vec4(1))*ofs*offsetMat;
		outcolor = vec4(rand(of.xy),rand(of.yz),rand(of.zx),1);
	}
}
