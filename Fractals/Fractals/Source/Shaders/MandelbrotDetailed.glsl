#version 460 core

layout(local_size_x = 8, local_size_y = 8, local_size_z = 1) in;

uniform ivec2 size;
uniform dvec2 scale;
uniform dvec2 pan;

uniform float lightHeight;
uniform vec2 lightDirection;
uniform float oddIterationsTint;
uniform float evenIterationsTint;
uniform uint maxIterations;

layout(rgba32f) restrict uniform image2D dataTexture;

dvec2 GetFractalPosition(ivec2 position)
{
    dvec2 scaledSize = size * scale;
    dvec2 normalizedPosition = position / scaledSize;
    dvec2 offsetPosition = normalizedPosition + pan;
    return (offsetPosition * 4) - (2 / scale); // Map both axis to [-2, 2]
}

dvec2 ComplexConj(dvec2 complex)
{
    return dvec2(complex.x, -complex.y);
}

dvec2 ComplexMul(dvec2 complex1, dvec2 complex2)
{
    return dvec2(
        (complex1.x * complex2.x) - (complex1.y * complex2.y),
        (complex1.x * complex2.y) + (complex1.y * complex2.x)
    );
}

dvec2 ComplexSquare(dvec2 complex)
{
    double squaredModulus = dot(complex, complex);
    float angle = atan(float(complex.y), float(complex.x));

    return dvec2(
        squaredModulus * cos(2 * angle),
        squaredModulus * sin(2 * angle)
    );
}

void ComputeMandelbrot(dvec2 fractalPosition, inout uint iterations, out float height)
{
    dvec2 criticalPoint = fractalPosition;
    dvec2 squaredDerivative = dvec2(0, 0);
    dvec2 derivative = dvec2(1, 0);

    while (dot(criticalPoint, criticalPoint) < 650 && iterations < maxIterations)
    {
        squaredDerivative = 2 * (ComplexMul(squaredDerivative, criticalPoint) + ComplexSquare(derivative));
        derivative = ComplexMul(derivative * 2, criticalPoint) + dvec2(1, 0);
		criticalPoint = ComplexMul(criticalPoint, criticalPoint) + fractalPosition;
        iterations++;
    }

    float squaredModulusLog = 0.5 * log(float(dot(criticalPoint, criticalPoint)));
    dvec2 normal = ComplexMul(ComplexMul(criticalPoint, derivative),
        ((squaredModulusLog + 1) * ComplexConj(ComplexSquare(derivative))) - (
            squaredModulusLog * ComplexConj(ComplexMul(criticalPoint, squaredDerivative))
        )
    );

    height = float(dot(normalize(normal), lightDirection) + lightHeight);
    height = max(0, height / (1 + lightHeight)); // Scale to [0, 1]
}

vec3 ComputeIterationsColor(float i)
{
    float r = 9 * (1 - i) * i * i * i;
    float g = 15 * (1 - i) * (1 - i) * i * i;
    float b = 8.5 * (1 - i) * (1 - i) * (1 - i) * i;
    return vec3(r, g, b);
}

void AlterOddIterationsColor(inout vec3 color, uint iterations, float multiplier)
{
    uint isOddMultiplier = iterations % 2;
    color += color * isOddMultiplier * multiplier;
}

void ApplyColorShading(inout vec3 color, float height)
{
    color = clamp(color, vec3(0), vec3(1));
    color *= height;
}

void main()
{
    ivec2 position = ivec2(gl_GlobalInvocationID.xy);

    if (position.x >= size.x || position.y >= size.y)
		return;

    float height;
    uint iterations = 0;
    dvec2 fractalPosition = GetFractalPosition(position);
    ComputeMandelbrot(fractalPosition, iterations, height);

    float normalizedIterations = iterations / float(maxIterations);
    vec3 color = ComputeIterationsColor(normalizedIterations);
    AlterOddIterationsColor(color, iterations, oddIterationsTint);
    AlterOddIterationsColor(color, iterations + 1, evenIterationsTint);
    ApplyColorShading(color, height);

    imageStore(dataTexture, position, vec4(color, 1));
}
