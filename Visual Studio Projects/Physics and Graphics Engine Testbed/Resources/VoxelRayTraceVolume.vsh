#version 330

layout(location = 0) in vec2 in_Position;

out vec2 vs_RayCoordinates;

void main()
{
    vs_RayCoordinates = in_Position;
    gl_Position = vec4(in_Position, 0.0, 1.0);    
}