#version 410 core

layout(location = 0) out vec4 color;

in vec2 texCoord;

uniform sampler2D utexture;

void main()
{
	color = texture(utexture, texCoord.xy);
}