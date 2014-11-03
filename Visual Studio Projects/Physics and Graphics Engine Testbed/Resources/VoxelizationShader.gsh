#version 420

#extension GL_ARB_shader_image_size : enable

layout(triangles, invocations = 1) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 vs_WorldPosition[];
in vec3 vs_WorldNormal[];

out vec3 gs_WorldPosition;
out vec3 gs_WorldNormal;
out vec4 gs_BBox;
out vec3 gs_Color;
out mat3 gs_SwizzleMatrixInv;

layout (binding = 0, rgba8) coherent uniform image3D volumeTexture;

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform float PixelDiagonal;
uniform bool ConservativeRasterization;

void expandTriangle(inout vec4 screenPos[3])
{
	vec2 edge[3];
	edge[0] = screenPos[1].xy - screenPos[0].xy;
	edge[1] = screenPos[2].xy - screenPos[1].xy;
	edge[2] = screenPos[0].xy - screenPos[2].xy;

	vec2 edgeNormal[3];
	edgeNormal[0] = normalize(edge[0]);
	edgeNormal[1] = normalize(edge[1]);
	edgeNormal[2] = normalize(edge[2]);
	edgeNormal[0] = vec2(-edgeNormal[0].y, edgeNormal[0].x);
	edgeNormal[1] = vec2(-edgeNormal[1].y, edgeNormal[1].x);
	edgeNormal[2] = vec2(-edgeNormal[2].y, edgeNormal[2].x);

    // If triangle is back facing, flip it's edge normals so triangle does not shrink.
    vec3 a = normalize(screenPos[1].xyz - screenPos[0].xyz);
	vec3 b = normalize(screenPos[2].xyz - screenPos[0].xyz);
	vec3 clipSpaceNormal = cross(a, b);
    if (clipSpaceNormal.z < 0.0)
    {
        edgeNormal[0] *= -1.0;
        edgeNormal[1] *= -1.0;
        edgeNormal[2] *= -1.0;
    }

	vec3 edgeDist;
	edgeDist.x = dot(edgeNormal[0], screenPos[0].xy);
	edgeDist.y = dot(edgeNormal[1], screenPos[1].xy);
	edgeDist.z = dot(edgeNormal[2], screenPos[2].xy);

	screenPos[0].xy = screenPos[0].xy - PixelDiagonal * (edge[2] / dot(edge[2], edgeNormal[0]) + edge[0] / dot(edge[0], edgeNormal[2]));
	screenPos[1].xy = screenPos[1].xy - PixelDiagonal * (edge[0] / dot(edge[0], edgeNormal[1]) + edge[1] / dot(edge[1], edgeNormal[0]));
	screenPos[2].xy = screenPos[2].xy - PixelDiagonal * (edge[1] / dot(edge[1], edgeNormal[2]) + edge[2] / dot(edge[2], edgeNormal[1]));
}

void main()
{
    // Calculate swizzle matrix based on eye space normal's dominant direction.
    vec3 eyeSpaceV1 = normalize(gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz);
	vec3 eyeSpaceV2 = normalize(gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz);
	vec3 eyeSpaceNormal = abs(cross(eyeSpaceV1, eyeSpaceV2));
	float dominantAxis = max(eyeSpaceNormal.x, max(eyeSpaceNormal.y, eyeSpaceNormal.z));
	mat3 swizzleMatrix;
	if (dominantAxis == eyeSpaceNormal.x)
    {
    	//z => x
    	//y => y
    	//x => z
		swizzleMatrix = mat3(vec3(0.0, 0.0, 1.0),
							 vec3(0.0, 1.0, 0.0),
							 vec3(1.0, 0.0, 0.0));
    }
	else if (dominantAxis == eyeSpaceNormal.y)
    {
    	//x => x
    	//z => y
    	//y => z
		swizzleMatrix = mat3(vec3(1.0, 0.0, 0.0),
						 	 vec3(0.0, 0.0, 1.0),
							 vec3(0.0, 1.0, 0.0));
    }
	else if (dominantAxis == eyeSpaceNormal.z)
    {
    	//x => x
    	//y => y
    	//z => z
		swizzleMatrix = mat3(vec3(1.0, 0.0, 0.0),
							 vec3(0.0, 1.0, 0.0),
							 vec3(0.0, 0.0, 1.0));
    }

    // Pass inverse of swizzle matrix to fragment shader.
    gs_SwizzleMatrixInv = inverse(swizzleMatrix);

    // Color code each triangle by which plane it projects to: (Red = x-axis, Green = y-axis, Blue = z-axis).
    gs_Color = swizzleMatrix * vec3(0.0, 0.0, 1.0);

    // Calculate screen coordinates for triangle.
	vec4 screenPos[3];
	screenPos[0] = ProjectionMatrix * vec4(swizzleMatrix * gl_in[0].gl_Position.xyz, 1.0);
	screenPos[1] = ProjectionMatrix * vec4(swizzleMatrix * gl_in[1].gl_Position.xyz, 1.0);
	screenPos[2] = ProjectionMatrix * vec4(swizzleMatrix * gl_in[2].gl_Position.xyz, 1.0);
    screenPos[0] /= screenPos[0].w;
    screenPos[1] /= screenPos[1].w;
    screenPos[2] /= screenPos[2].w;
    
    // Calculate screen space bounding box to be used for clipping in the fragment shader.
    gs_BBox.xy = min(screenPos[0].xy, min(screenPos[1].xy, screenPos[2].xy));
    gs_BBox.zw = max(screenPos[0].xy, max(screenPos[1].xy, screenPos[2].xy));
    gs_BBox.xy -= vec2(PixelDiagonal);
    gs_BBox.zw += vec2(PixelDiagonal);

    // Expand triangle for conservative rasterization.
    if (ConservativeRasterization)
    {
        expandTriangle(screenPos);
    }
    
    // Output triangle.
	gs_WorldPosition = vs_WorldPosition[0];
	gs_WorldNormal = vs_WorldNormal[0];
	gl_Position = screenPos[0];
	EmitVertex();

	gs_WorldPosition = vs_WorldPosition[1];
	gs_WorldNormal = vs_WorldNormal[1];
	gl_Position = screenPos[1];
	EmitVertex();

	gs_WorldPosition = vs_WorldPosition[2];
	gs_WorldNormal = vs_WorldNormal[2];
	gl_Position = screenPos[2];
	EmitVertex();

	EndPrimitive();
}