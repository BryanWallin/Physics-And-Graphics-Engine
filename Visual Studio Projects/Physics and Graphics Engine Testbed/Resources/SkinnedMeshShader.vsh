#version 430

attribute vec4 position;
attribute vec3 normal;
attribute vec2 boneWeights;
attribute vec2 boneIndices;

uniform mat4 worldToEyeMatrix[4];
uniform mat4 projectionMatrix;

varying lowp vec4 colorVarying;

void main()
{
    colorVarying = vec4(boneWeights.x, boneWeights.y,
                        boneIndices.x + boneIndices.y, 1);
    
    vec4 worldToEye = (boneWeights.x * worldToEyeMatrix[int(boneIndices.x)] +
                   boneWeights.y * worldToEyeMatrix[int(boneIndices.y)]) *
                  position;
    //worldToEye = worldToEyeMatrix[1] * position;
    
    gl_Position = projectionMatrix * worldToEye;
}