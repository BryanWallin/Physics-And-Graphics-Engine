#version 420

//Attributes
varying lowp vec3 positionVarying;
varying lowp vec3 normalVarying;

//Uniforms
uniform sampler3D VolumeTexture;
uniform float distanceReduce;
uniform float coneRatio;
uniform vec4 diffuseColor;
uniform vec4 emissiveColor;

//This method traces a cone and accumulates ambient occlusion.
//
//<param="coneOrigin">The origin of the cone, in texture space.<param>
//<param="coneDirection">The direction of the cone.<param>
//<param="coneRatio">The ratio of the cone height to width.  A value 
//of 2 means the cone has an angle of 90 degrees.<param>
float coneTrace(vec3 coneOrigin, vec3 coneDirection, float coneRatio, float coneOffset)
{
	vec3 position = coneOrigin;
	float occlusion = 0.0;
	float distance = 0.0;

	//Tracing the cone.
	for (int i = 0; i < 128; ++i)
	{
		//Computing sample size and mipmap level.
		float sampleSize = distance * coneRatio;
		if(sampleSize < 0.000001)
			sampleSize = 1.0 / 128.0;

		float mipmapLevel = log2(sampleSize * 128.0);
		if(mipmapLevel < 0)
			mipmapLevel = 0;

		//Getting the occlusion.
		occlusion += (textureLod(VolumeTexture, position, mipmapLevel).a / (1 + distanceReduce * (distance + coneOffset)));

		float stepSize = sampleSize;
		distance += stepSize;
		position = coneOrigin + coneDirection * distance;

		if(occlusion > 0.95 || 
			position.x > 1.0 || position.x < 0.0 ||
      		position.y > 1.0 || position.y < 0.0 ||
      		position.z > 1.0 || position.z < 0.0)
			break;
	}

	return occlusion;
}

vec4 coneTraceDebug(vec3 coneOrigin, vec3 coneDirection, float coneRatio, float coneOffset)
{
	vec3 position = coneOrigin;
	float occlusion = 0.0;
	float distance = 0.0;
	vec3 colorOcclusion = vec3(0, 0, 0);
	int i = 0;

	//Tracing the cone.
	for (i = 0; i < 128; ++i)
	{
		//Computing sample size and mipmap level.
		float sampleSize = distance * coneRatio;
		if(sampleSize < 0.000001)
			sampleSize = 1.0 / 128.0;

		float mipmapLevel = log2(sampleSize * 128.0);
		if(mipmapLevel < 0)
			mipmapLevel = 0;

		//Getting the occlusion.
		vec4 textureValue = textureLod(VolumeTexture, position, mipmapLevel);
		occlusion += textureValue.a;
		colorOcclusion.rgb += textureValue.rgb;// * (textureValue.a);

		float stepSize = sampleSize / 3.33333;
		distance += stepSize;
		position = coneOrigin + coneDirection * distance;

		if(occlusion > 0.95 || 
			position.x > 1.0 || position.x < 0.0 ||
      		position.y > 1.0 || position.y < 0.0 ||
      		position.z > 1.0 || position.z < 0.0)
			break;
	}

	return vec4(colorOcclusion, diffuseColor.a);
}

void main()
{
	vec3 texturePosition = vec3(0.5, 0.5, 0.5) * (positionVarying + vec3(1.0, 1.0, 1.0));

	//Solving for two perpendicular (to the normal) vectors.
	vec3 tangent;
	if(abs(normalVarying.z) > 0.000001 || abs(normalVarying.y) > 0.000001)
		tangent = normalize(vec3(0, -normalVarying.z, normalVarying.y));
	else
		tangent = normalize(vec3(-normalVarying.z, 0, normalVarying.x));

	vec3 bitangent = normalize(cross(tangent, normalVarying));

	//Solving for the cone tracing attributes.
	float coneOffset = 1 / 128.0;
	vec3 coneStartingPosition = texturePosition + coneOffset * normalize(normalVarying);
	vec3 cone1Direction = normalize(normalVarying);
	vec3 cone2Direction = normalize(normalVarying + tangent);
	vec3 cone3Direction = normalize(normalVarying - tangent);
	vec3 cone4Direction = normalize(normalVarying + bitangent);
	vec3 cone5Direction = normalize(normalVarying - bitangent);
	float coneRatio = coneRatio;

	//Tracing the cones.
	float ambientOcclusion1 = coneTrace(coneStartingPosition, cone1Direction, coneRatio, coneOffset);
	float ambientOcclusion2 = coneTrace(coneStartingPosition, cone2Direction, coneRatio, coneOffset);
	float ambientOcclusion3 = coneTrace(coneStartingPosition, cone3Direction, coneRatio, coneOffset);
	float ambientOcclusion4 = coneTrace(coneStartingPosition, cone4Direction, coneRatio, coneOffset);
	float ambientOcclusion5 = coneTrace(coneStartingPosition, cone5Direction, coneRatio, coneOffset);

	if(emissiveColor.a < 1)
	{
		vec4 colorOcclusion1 = coneTraceDebug(coneStartingPosition, cone1Direction, coneRatio, coneOffset);
		vec4 colorOcclusion2 = coneTraceDebug(coneStartingPosition, cone2Direction, coneRatio, coneOffset);
		vec4 colorOcclusion3 = coneTraceDebug(coneStartingPosition, cone3Direction, coneRatio, coneOffset);
		vec4 colorOcclusion4 = coneTraceDebug(coneStartingPosition, cone4Direction, coneRatio, coneOffset);
		vec4 colorOcclusion5 = coneTraceDebug(coneStartingPosition, cone5Direction, coneRatio, coneOffset);

		vec4 totalColorOcclusion = (colorOcclusion1 + colorOcclusion2 + colorOcclusion3 + colorOcclusion4 + colorOcclusion5) / 1.0;

	    gl_FragColor = vec4(emissiveColor.r + diffuseColor.r * totalColorOcclusion.r,// - totalColorOcclusion.a, 
	    					emissiveColor.g + diffuseColor.g * totalColorOcclusion.g,// - totalColorOcclusion.a, 
	    					emissiveColor.b + diffuseColor.b * totalColorOcclusion.b,// - totalColorOcclusion.a, 
	    					1);	
	}
	else
	{
		gl_FragColor = emissiveColor;
	}
}