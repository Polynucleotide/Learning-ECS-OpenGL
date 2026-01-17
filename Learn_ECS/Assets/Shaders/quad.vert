#version 450 core

// In
layout (location = 0) in vec4 aColor;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float aSampler;
layout (location = 3) in mat3 aInstancedTransform;

// Out
layout (location = 0) out vec4 vColor;
layout (location = 1) out vec2 vTexCoord;
layout (location = 2) out flat int vSampler;

// Uniform
uniform mat3 u_world_to_ndc_mtx;

vec2 quadVertices[4] = {
	{ -0.5f,  0.5f },
	{ -0.5f, -0.5f },
	{  0.5f,  0.5f },
	{  0.5f, -0.5f }
};

void main() {
	gl_Position = vec4(u_world_to_ndc_mtx * aInstancedTransform * vec3(quadVertices[gl_VertexID], 1.f), 1.f);
	vColor = vec4(aTexCoord, 0.f, 1.f);
	vTexCoord = aTexCoord;
	vSampler = int(aSampler);
}
