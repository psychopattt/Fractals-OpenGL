#version 460 core

layout(local_size_x = 8, local_size_y = 8, local_size_z = 1) in;

uniform ivec2 size;
uniform dvec2 scale;
uniform dvec2 pan;

uniform uint maxIterations;
uniform dvec2 constant;

layout(rgba32f) restrict uniform image2D dataTexture;

dvec2 GetFractalPosition(ivec2 position)
{
    dvec2 scaledSize = size * scale;
    dvec2 normalizedPosition = position / scaledSize;
    dvec2 offsetPosition = normalizedPosition + pan;
    return (offsetPosition * 4) - (2 / scale); // Map both axis to [-2, 2]
}

int ComputeJulia(dvec2 fractalPosition)
{
    int iterations = 0;
    dvec2 criticalPoint = fractalPosition;

    while (dot(criticalPoint, criticalPoint) < 4 && iterations < maxIterations)
    {
        iterations++;
        criticalPoint = constant + dvec2(
            (criticalPoint.x * criticalPoint.x) - (criticalPoint.y * criticalPoint.y),
            2 * criticalPoint.x * criticalPoint.y
        );
    }

    return iterations;
}

vec4 ComputeColor(float i)
{
    float r = 9 * (1 - i) * i * i * i;
    float g = 15 * (1 - i) * (1 - i) * i * i;
    float b = 8.5 * (1 - i) * (1 - i) * (1 - i) * i;
    return vec4(r, g, b, 1);
}

void main()
{
    ivec2 position = ivec2(gl_GlobalInvocationID.xy);

    if (position.x >= size.x || position.y >= size.y)
		return;

    dvec2 fractalPosition = GetFractalPosition(position);
    int iterations = ComputeJulia(fractalPosition);

    float normalizedIterations = iterations / float(maxIterations);
    imageStore(dataTexture, position, ComputeColor(normalizedIterations));
}
