#version 410 core

layout(location = 0) out vec4 color;

in vec3 texCoord_frag;

void main()
{
color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	//color = vec4(texCoord_frag, 1.0f);
}