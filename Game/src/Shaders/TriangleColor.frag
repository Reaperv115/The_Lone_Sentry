#version 410 core

layout(location = 0) out vec4 color;

in vec3 texCoord;

void main()
{
	color = vec4(texCoord, 1.0f);
}