#version 430

attribute vec4 position;
attribute vec3 normal;

varying lowp vec4 colorVarying;

uniform mat4 currentModelView;
uniform mat3 currentNormalMatrix;

void main()
{
    vec3 eyeNormal = normalize(currentNormalMatrix * normal);
    vec3 lightPosition = vec3(0.0, 0.0, 1.0);
    vec4 diffuseColor = vec4(0.4, 0.4, 1.0, 1.0);
    
    float nDotVP = max(0.0, dot(eyeNormal, normalize(lightPosition)));
                 
    colorVarying = diffuseColor * nDotVP;
    
    gl_PointSize = 10.0;
    gl_Position = currentModelView * position;
}