#pragma once
#include "Core.h"

namespace Engine
{
	class ConstantBuffer
	{
	public:
		ConstantBuffer(unsigned int size, unsigned int bindingslot);
		~ConstantBuffer();

		void Bind() const;
		void UnBind() const;

		void SetData(const void* data, unsigned int size, unsigned int offset = 0);
	private:
		unsigned int id;
		unsigned int slot;
	};
}

