#version 460 core

layout(local_size_x = 8, local_size_y = 8, local_size_z = 1) in;

uniform ivec2 size;
uniform dvec2 scale;
uniform dvec2 pan;

uniform uint maxDepth;
uniform bool gradientInvert;
uniform float gradientBrightness;
uniform double gradientRepetition;

layout(rgba32f) restrict uniform image2D dataTexture;

dvec2 GetFractalPosition(ivec2 position)
{
    dvec2 scaledSize = size * scale;
    dvec2 normalizedPosition = position / scaledSize;
    dvec2 offsetPosition = normalizedPosition + pan;
    return offsetPosition - (0.5 / scale) + 0.5; // Map both axis to [0, 1]
}

bool ComputeSierpinski(dvec2 position)
{
	double blockSize = 1;

    for (uint depth = 0; depth < maxDepth; depth++)
    {
        blockSize /= 3;
        position = mod(position, dvec2(blockSize * 2));

        if (position.x > blockSize && position.y > blockSize)
            return true;

        position = mod(position, dvec2(blockSize));
    }

    return false;
}

dvec3 HsvToRgb(dvec3 c)
{
    dvec4 K = dvec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    dvec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

vec3 ComputeColor(dvec2 fractalPosition)
{
    double centerDistance = distance(fractalPosition, dvec2(0.5));
    double gradientPosition = centerDistance * gradientRepetition;

    dvec3 hsvColor = mix(dvec3(0, 1, 1), dvec3(1), gradientPosition);
    vec3 rgbColor = vec3(HsvToRgb(hsvColor));

    return rgbColor;
}

void ApplyColorSettings(inout vec3 color, bool insideFractal)
{
    int invertMultiplier = abs(int(gradientInvert) - int(insideFractal));
    color *= invertMultiplier * gradientBrightness;
}

void main()
{
    ivec2 position = ivec2(gl_GlobalInvocationID.xy);

    if (position.x >= size.x || position.y >= size.y)
		return;

    dvec2 fractalPosition = GetFractalPosition(position);
    bool inside = ComputeSierpinski(fractalPosition);
    vec3 color = ComputeColor(fractalPosition);
    ApplyColorSettings(color, inside);

    imageStore(dataTexture, position, vec4(color, 1));
}
