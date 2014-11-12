#version 420

#define ATTRIB_POSITION     0
#define ATTRIB_COLOR        1
#define ATTRIB_NORMAL       2
#define ATTRIB_TEXCOORD0    3
#define ATTRIB_TANGENT      4
#define ATTRIB_BITANGENT    5

attribute vec3 position;
attribute vec3 normal;

out vec3 vs_WorldPosition;
out vec3 vs_WorldNormal;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

void main()
{	
	vs_WorldPosition = (modelMatrix * vec4(position, 1.0)).xyz;
	vs_WorldNormal = (modelMatrix * vec4(normal, 0.0)).xyz;
    gl_Position = modelMatrix * vec4(position, 1.0);
}