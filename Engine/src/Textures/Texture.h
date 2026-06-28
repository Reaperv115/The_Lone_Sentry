#pragma once
#include "Core.h"
#include <string>


namespace Engine
{
	class Texture
	{
	public:
		Texture(const std::string& filepath);
		~Texture();

		void Bind(unsigned int slot = 0) const;
		void UnBind();

		int GetWidth() const { return width; }
		int GetHeight() const { return height; }

	private:
		unsigned int id;
		int width, height, channels;
	};
}

