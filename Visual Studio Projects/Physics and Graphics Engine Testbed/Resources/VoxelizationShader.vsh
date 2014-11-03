#version 420

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

uniform mat4 ProjectionMatrix;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;

void main()
{	
	vs_WorldPosition = (ModelMatrix * vec4(in_Position, 1.0)).xyz;
	vs_WorldNormal = (ModelMatrix * vec4(in_Normal, 0.0)).xyz;
    gl_Position = ViewMatrix * ModelMatrix * vec4(in_Position, 1.0);
}