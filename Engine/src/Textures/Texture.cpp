#include "gepch.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#include "Texture.h"

Engine::Texture::Texture(const std::string& filepath)
	: id(0), width(0), height(0), channels(0)
{
	stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, 4);

	if (!data)
	{
		std::cout << "Failed to load texture: " << filepath << std::endl;
		return;
	}

	Call(glGenTextures(1, &id));
	Call(glBindTexture(GL_TEXTURE_2D, id));

	Call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	Call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	Call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	Call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	Call(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));

	Call(glBindTexture(GL_TEXTURE_2D, 0));
	stbi_image_free(data);
}

Engine::Texture::~Texture()
{
	Call(glDeleteTextures(1, &id));
}

void Engine::Texture::Bind(unsigned int slot /*= 0*/) const
{
	Call(glActiveTexture(GL_TEXTURE0 + slot));
	Call(glBindTexture(GL_TEXTURE_2D, id));
}

void Engine::Texture::UnBind()
{
	Call(glBindTexture(GL_TEXTURE_2D, 0));
}
