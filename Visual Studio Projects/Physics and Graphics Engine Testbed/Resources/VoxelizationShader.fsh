#version 430

in vec3 gs_WorldPosition;
in vec3 gs_WorldNormal;
in vec4 gs_BBox;
in vec3 gs_Color;
in mat3 gs_SwizzleMatrixInv;

layout (binding = 0, rgba8) coherent uniform image3D volumeTexture;
layout (location = 0) out vec4 FragColor;

uniform vec4 LightPosition;
uniform vec3 LightAmbient;
uniform vec3 LightDiffuse;
uniform vec3 MaterialKa;
uniform vec3 MaterialKd;
uniform bool colorCode;
uniform float pixelDiagonal;
uniform bool conservativeRasterization;

vec3 PhongModel()
{
	vec3 lightDir;
	if (LightPosition.w == 1.0) lightDir = normalize(LightPosition.xyz - gs_WorldPosition);
    else lightDir = normalize(-LightPosition.xyz);

	vec3 normal = normalize(gs_WorldNormal);

    vec3 r = normalize(reflect(-lightDir, normal));
 
    vec3 ambient = LightAmbient * MaterialKa;
    float sDotN = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = LightDiffuse * MaterialKd * sDotN;
    return ambient + diffuse;
}

void main()
{
    ivec2 viewportSize = ivec2(128, 128);
    vec2 bboxMin = floor((gs_BBox.xy * 0.5 + 0.5) * viewportSize);
	vec2 bboxMax = ceil((gs_BBox.zw * 0.5 + 0.5) * viewportSize);

    imageStore(volumeTexture, ivec3(0,0,0), vec4(1.0, 1.0, 1.0, 1.0));

	//if (all(greaterThanEqual(gl_FragCoord.xy, bboxMin)) && all(lessThanEqual(gl_FragCoord.xy, bboxMax)))
	//{
    //    vec3 fragmentColor = PhongModel();
    //    if (ColorCode) fragmentColor *= gs_Color;
    //    vec3 coords = gs_SwizzleMatrixInv * vec3(gl_FragCoord.xy, gl_FragCoord.z * viewportSize.x);
    //    imageStore(volumeTexture, ivec3(coords), vec4(fragmentColor, 1.0));
    //}
    //else
    //{
    //    discard;
    //}
}