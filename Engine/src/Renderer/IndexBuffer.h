#pragma once

#include "Core.h"

namespace Engine
{
	class IndexBuffer
	{
	public:
		IndexBuffer(const unsigned int* data, const unsigned int indexcount);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

	private:
		unsigned int id;
		unsigned int indexCount;
	};
}

