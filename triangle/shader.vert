#version 460 core

layout(location = 0) in vec3 pos;
//layout(location = 1) in vec2 texturecoordinates;
layout(location = 1) in vec3 shadercolor;

out vec2 Texcoord;
out vec3 colorvec;
//uniform float x_offset;
//uniform float y_offset;
uniform mat4 TrMatrix;
uniform float time;
const float pi = 3.14159265f;


void main(){
	gl_Position = TrMatrix * vec4(pos.x, pos.y, pos.z, 1.0f);
	colorvec = shadercolor;
	//colorvec = 0.5 + 0.5*cos(time*2+ 1/gl_Position.xyx+vec3(0,2,4));;
}
