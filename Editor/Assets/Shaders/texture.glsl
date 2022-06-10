#type vertex
#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

layout (location = 0) out vec3 vPos;
layout (location = 1) out vec2 vTexCoord;

uniform mat4 uViewProj;
uniform mat4 uModelMat;

void main()
{
	vPos = aPos;
	vTexCoord = aTexCoord;
	gl_Position = uViewProj * uModelMat * vec4(vPos, 1.0f);
}

#type fragment
#version 460 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vTexCoord;
layout (location = 0) out vec4 fragColor;

uniform sampler2D uTexture;

void main()
{
	fragColor = texture(uTexture, vTexCoord);
}