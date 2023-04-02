#version 330 core
out vec4 FragColor;  
in vec3 bsColor;

void main()
{
    FragColor = vec4(bsColor, 1.0);
}