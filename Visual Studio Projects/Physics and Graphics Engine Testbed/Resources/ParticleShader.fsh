#version 430

varying lowp vec4 colorVarying;
uniform sampler2D diffuse;

void main()
{
    gl_FragColor = colorVarying * texture2D(diffuse, gl_PointCoord.st);
}