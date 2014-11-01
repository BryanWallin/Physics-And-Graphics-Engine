#version 430

uniform sampler2D diffuse;
varying lowp vec2 textureCoordinates;

void main()
{
    gl_FragColor = texture2D(diffuse, textureCoordinates);
}