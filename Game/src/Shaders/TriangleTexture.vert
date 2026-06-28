layout(location = 0) in vec3 position;
layout(location = 1) in vec2 color;

out vec2 texCoord;

layout(std140) uniform CameraData
{
	mat4 transform;
};

void main()
{
	gl_Position = transform * vec4(position, 1.0f);
	texCoord = color;
}