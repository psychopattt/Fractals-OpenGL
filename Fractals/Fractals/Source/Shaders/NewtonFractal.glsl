#version 460 core

layout(local_size_x = 8, local_size_y = 8, local_size_z = 1) in;

uniform ivec2 size;
uniform dvec2 scale;
uniform dvec2 pan;

uniform uint roots;
uniform uint maxIterations;
uniform float colorMultiplier;
uniform float colorShift;

const float tau = 6.283185307;
const double threshold = 0.00000000001;

layout(rgba32f) restrict uniform image2D dataTexture;

dvec2 GetFractalPosition(ivec2 position)
{
    dvec2 scaledSize = size * scale;
    dvec2 normalizedPosition = position / scaledSize;
    dvec2 offsetPosition = normalizedPosition + pan;
    return (offsetPosition * 4) - (2 / scale); // Map both axis to [-2, 2]
}

dvec2 ComplexMul(dvec2 complex1, dvec2 complex2)
{
    return dvec2(
        (complex1.x * complex2.x) - (complex1.y * complex2.y),
        (complex1.x * complex2.y) + (complex1.y * complex2.x)
    );
}

dvec2 ComplexDiv(dvec2 complex1, dvec2 complex2)
{
    double divisor = (complex2.x * complex2.x) + (complex2.y * complex2.y);

    return dvec2(
        ((complex1.x * complex2.x) + (complex1.y * complex2.y)) / divisor,
        ((complex1.y * complex2.x) - (complex1.x * complex2.y)) / divisor
    );
}

dvec2 ComplexPow(dvec2 complex, uint exponent)
{
    dvec2 result = dvec2(1, 0);

    while (exponent > 0)
    {
        if ((exponent & 1) == 1)
            result = ComplexMul(result, complex);

        complex = ComplexMul(complex, complex);
        exponent >>= 1;
    }

    return result;
}

void ComputeNewton(inout uint iterations, inout dvec2 criticalPoint)
{
	dvec2 stepDifference = dvec2(1);

    while (dot(stepDifference, stepDifference) > threshold && iterations < maxIterations)
    {
        stepDifference = criticalPoint;

        dvec2 derivativePower = ComplexPow(criticalPoint, roots - 1);
        dvec2 functionPower = ComplexMul(derivativePower, criticalPoint);
        criticalPoint -= ComplexDiv(functionPower - dvec2(1, 0), roots * derivativePower);

        stepDifference -= criticalPoint;
        iterations++;
    }
}

vec3 HsvToRgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

vec3 ComputeColor(uint iterations, vec2 criticalPoint)
{
    float value = 1 - (iterations / float(maxIterations));
    float hue = atan(criticalPoint.y, criticalPoint.x) /
        tau * colorMultiplier + colorShift;

    return HsvToRgb(vec3(hue, 1, value));
}

void main()
{
    ivec2 position = ivec2(gl_GlobalInvocationID.xy);

    if (position.x >= size.x || position.y >= size.y)
		return;

    uint iterations = 0;
    dvec2 criticalPoint = GetFractalPosition(position);
    ComputeNewton(iterations, criticalPoint);

    vec3 color = ComputeColor(iterations, vec2(criticalPoint));
    imageStore(dataTexture, position, vec4(color, 1));
}
