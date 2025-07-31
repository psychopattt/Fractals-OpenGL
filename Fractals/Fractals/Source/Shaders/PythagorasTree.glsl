#version 460 core

layout(local_size_x = 8, local_size_y = 8, local_size_z = 1) in;

uniform ivec2 size;
uniform dvec2 scale;
uniform dvec2 pan;

uniform uint maxOrder;
uniform vec3 trunkColor;
uniform vec3 leavesColor;
uniform bool mergeBranches;

const double squareSize = 0.05;
const dvec2 squareOffset = dvec2(squareSize, squareSize * 2);
const dvec2 treeCenter = dvec2(0, squareSize * 3);

layout(rgba32f) restrict uniform image2D dataTexture;

dvec2 GetFractalPosition(ivec2 position)
{
    dvec2 scaledSize = size * scale;
    dvec2 normalizedPosition = position / scaledSize;
    dvec2 offsetPosition = normalizedPosition + pan + treeCenter;
    return (offsetPosition - (0.5 / scale)); // Map both axis to [0, 1]
}

bool InsideSquare(dvec2 position)
{
    double y = mergeBranches ? position.y : abs(position.y);
    return abs(position.x) < squareSize && y < squareSize;
}

bool ComputeTree(dvec2 position, inout uint order)
{
    bool inside = InsideSquare(position);

    while (!inside && order < maxOrder)
    {
        position.x = abs(position.x);
        position -= squareOffset;
        position += dvec2(-position.y, position.x);

        inside = InsideSquare(position);
        order++;
    }

    return inside;
}

vec3 ComputeColor(uint order, bool inside)
{
    float slopePosition = order / float(clamp(maxOrder, 1u, 16u));
    float mixAmount = smoothstep(0.2, 0.8, slopePosition);
    vec3 color = mix(trunkColor, leavesColor, mixAmount);

    return color * int(inside);
}

void main()
{
    ivec2 position = ivec2(gl_GlobalInvocationID.xy);

    if (position.x >= size.x || position.y >= size.y)
		return;

    uint order = 0;
    dvec2 fractalPosition = GetFractalPosition(position);
    bool inside = ComputeTree(fractalPosition, order);

    vec3 color = ComputeColor(order, inside);
    imageStore(dataTexture, position, vec4(color, 1));
}
