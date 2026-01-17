#version 450 core

// In
layout (location = 0) in vec4 vColor;
layout (location = 1) in vec2 vTexCoord;
layout (location = 2) in flat int vSampler;

// Out
out vec4 fragColor;

// Uniform
uniform sampler2D uSamplers[gl_MaxTextureImageUnits];

void main() {
	fragColor = texture(uSamplers[vSampler], vTexCoord);
}
