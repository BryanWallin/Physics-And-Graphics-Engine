#version 420

#extension GL_ARB_shader_image_size : enable

struct LightInfo
{
    vec4 Position;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

struct MaterialInfo
{
    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
    float Shininess;
};

in vec3 gs_WorldPosition;
in vec3 gs_WorldNormal;
in vec4 gs_BBox;
in vec3 gs_Color;
in mat3 gs_SwizzleMatrixInv;

layout (binding = 0, rgba8) coherent uniform image3D volumeTexture;
layout (location = 0) out vec4 FragColor;

uniform LightInfo Light0;
uniform MaterialInfo Material0;
uniform bool ColorCode;
uniform float PixelDiagonal;
uniform bool ConservativeRasterization;

vec3 PhongModel()
{
	vec3 lightDir;
	if (Light0.Position.w == 1.0) lightDir = normalize(Light0.Position.xyz - gs_WorldPosition);
    else lightDir = normalize(-Light0.Position.xyz);

	vec3 normal = normalize(gs_WorldNormal);

    vec3 r = normalize(reflect(-lightDir, normal));
 
    vec3 ambient = Light0.Ambient * Material0.Ka;
    float sDotN = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = Light0.Diffuse * Material0.Kd * sDotN;
    return ambient + diffuse;
}

void main()
{
    ivec2 viewportSize = imageSize(volumeTexture).xy;
    vec2 bboxMin = floor((gs_BBox.xy * 0.5 + 0.5) * viewportSize);
	vec2 bboxMax = ceil((gs_BBox.zw * 0.5 + 0.5) * viewportSize);
	if (all(greaterThanEqual(gl_FragCoord.xy, bboxMin)) && all(lessThanEqual(gl_FragCoord.xy, bboxMax)))
	{
        vec3 fragmentColor = PhongModel();
        if (ColorCode) fragmentColor *= gs_Color;
        vec3 coords = gs_SwizzleMatrixInv * vec3(gl_FragCoord.xy, gl_FragCoord.z * viewportSize.x);
        imageStore(volumeTexture, ivec3(coords), vec4(fragmentColor, 1.0));
    }
    else
    {
        discard;
    }
}