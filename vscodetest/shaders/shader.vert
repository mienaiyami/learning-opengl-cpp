#version 330 core
layout (location = 0) in vec3 aPos;  
out vec3 bsColor;
void main()
{
    gl_Position = vec4(aPos,1.0f );
    bsColor = aPos; 
    bsColor.z=(bsColor.x+bsColor.y)*(-1);
    if(bsColor.x==0.0 &&bsColor.y==0.0 &&bsColor.z==0.0) bsColor = vec3(1.0,1.0,1.0);
}