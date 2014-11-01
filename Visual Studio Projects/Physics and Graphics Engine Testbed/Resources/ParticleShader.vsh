#version 430

attribute vec4 position;
attribute vec4 color;
attribute float size;

uniform mat4 worldToEyeMatrix;

varying lowp vec4 colorVarying;

void main()
{
    colorVarying = color;
    
    gl_PointSize = size;
    gl_Position =  worldToEyeMatrix * position;
}