#version 430

varying lowp vec4 colorVarying;
varying lowp vec2 textureCoordinateVarying;
uniform sampler2D diffuse;

void main()
{
    gl_FragColor = colorVarying;
}