#version 460 core

layout(local_size_x = 8, local_size_y = 8, local_size_z = 1) in;

uniform ivec2 size;
uniform dvec2 scale;
uniform dvec2 pan;
uniform uint maxIterations;

restrict writeonly uniform image2D dataTexture;

dvec2 GetFractalPosition(ivec2 position)
{
    dvec2 scaledSize = size * scale;
    dvec2 normalizedPosition = position / scaledSize;
    dvec2 offsetPosition = normalizedPosition + pan;
    return (offsetPosition * 4) - (2 / scale); // Map both axis to [-2, 2]
}

int ComputeMandelbrot(dvec2 fractalPosition)
{
    int iterations = 0;
    dvec2 point1 = dvec2(0);
    dvec2 point2 = dvec2(0);

    while (point2.x + point2.y < 4 && iterations < maxIterations)
    {
        point1.y = 2 * point1.x * point1.y + fractalPosition.y;
        point1.x = point2.x - point2.y + fractalPosition.x;
        point2 = point1 * point1;
        iterations++;
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
    int iterations = ComputeMandelbrot(fractalPosition);

    float normalizedIterations = iterations / float(maxIterations);
    imageStore(dataTexture, position, ComputeColor(normalizedIterations));
}
