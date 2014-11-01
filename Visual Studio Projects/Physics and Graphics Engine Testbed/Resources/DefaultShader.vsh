#version 430

attribute vec4 position;
attribute vec3 normal;
attribute vec2 textureCoordinate;

uniform mat4 worldToEyeMatrix;
uniform mat4 modelToWorldMatrix;

varying lowp vec4 colorVarying;
varying vec2 textureCoordinateVarying;

void main()
{
    colorVarying = worldToEyeMatrix * position;
    textureCoordinateVarying = textureCoordinate;
    
    gl_Position = worldToEyeMatrix * position;
}