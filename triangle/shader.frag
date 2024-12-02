#version 460 core

in vec3 colorvec;
//in vec2 Texcoord;

//uniform float opacity;

//uniform sampler2D texture1;
//uniform sampler2D texture2;

out vec4 fragcolor;
void main() {
	//fragcolor = mix(texture(texture1, vec2(Texcoord.x, Texcoord.y)), texture(texture2, vec2(Texcoord.x * 1, Texcoord.y * 1)), opacity);
	fragcolor = vec4(colorvec.xyz, 1.0f);
}