#version 430

attribute vec4 position;
attribute vec3 normal;

uniform mat4 worldToEyeMatrix;
uniform mat4 modelToWorldMatrix;

varying lowp vec4 colorVarying;

void main()
{
    colorVarying = vec4(1, 0.25, 0.25, 1);
    
    gl_Position =  worldToEyeMatrix * modelToWorldMatrix * position;
}