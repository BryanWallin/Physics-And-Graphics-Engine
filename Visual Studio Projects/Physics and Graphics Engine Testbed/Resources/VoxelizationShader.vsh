#version 430

#define ATTRIB_POSITION     0
#define ATTRIB_COLOR        1
#define ATTRIB_NORMAL       2
#define ATTRIB_TEXCOORD0    3
#define ATTRIB_TANGENT      4
#define ATTRIB_BITANGENT    5

layout (location = ATTRIB_POSITION) in vec3 in_Position;
layout (location = ATTRIB_NORMAL) in vec3 in_Normal;

out vec3 vs_WorldPosition;
out vec3 vs_WorldNormal;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

void main()
{	
	vs_WorldPosition = (modelMatrix * vec4(in_Position, 1.0)).xyz;
	vs_WorldNormal = (modelMatrix * vec4(in_Normal, 0.0)).xyz;
    gl_Position = modelMatrix * vec4(in_Position, 1.0);
}