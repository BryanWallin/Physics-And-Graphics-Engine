#version 430

attribute vec4 position;
attribute vec3 normal;
attribute vec2 textureCoordinate;

uniform mat4 worldToEyeMatrix;
uniform mat4 projectionMatrix;

varying lowp vec2 textureCoordinates;

void main()
{
    textureCoordinates = textureCoordinate;
    
    gl_Position =  projectionMatrix * worldToEyeMatrix * position;
}