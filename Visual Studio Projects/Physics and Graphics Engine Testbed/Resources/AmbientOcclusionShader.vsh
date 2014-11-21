#version 430

attribute vec4 position;
attribute vec3 normal;

uniform mat4 worldEyeMatrix;
uniform mat4 modelWorldMatrix;

varying lowp vec3 positionVarying;
varying lowp vec3 normalVarying;

void main()
{
    vec4 worldPosition = modelWorldMatrix * position;
    positionVarying = worldPosition.xyz;
    normalVarying = normal;

    gl_Position =  worldEyeMatrix * worldPosition;
}