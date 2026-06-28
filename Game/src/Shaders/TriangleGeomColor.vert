#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec3 texCoord_frag;

layout(std140) uniform CameraData
{
	mat4 transform;
};

void main()
{
	gl_Position = transform * vec4(position , 1.0f);
	texCoord_frag = color;
}