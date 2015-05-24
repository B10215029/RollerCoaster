#version 430

out vec2 texcoord;
const vec4 vertexs[4]=vec4[](
	vec4(-1,-1,0.5,1),
	vec4(1,-1,0.5,1),
	vec4(1,1,0.5,1),
	vec4(-1,1,0.5,1)
	);
void main(){
	texcoord = (vertexs[gl_VertexID].xy + vec2(1))/2;
	gl_Position = vertexs[gl_VertexID];
}
