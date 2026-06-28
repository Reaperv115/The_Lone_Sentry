#pragma once
#include <vector>
#include "glad/glad.h"


namespace Engine
{

	struct VertexBufferElements
	{
		unsigned int type;
		unsigned int count;
		unsigned int normalized;

		static unsigned int GetSizeOfType(unsigned int type)
		{
			switch (type)
			{
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
			}
		}
	};

	class VertexBufferLayout
	{
	private:
		std::vector<VertexBufferElements> elements;
		unsigned int stride;
	public:
		VertexBufferLayout()
			: stride(0)
		{}

		template<typename T>
		void Push(int count)
		{
			static_assert(false, "unsupported type");
		}

		template<>
		void Push<float>(int count);
		
		template<>
		void Push<unsigned int>(int count);

		template<>
		void Push<unsigned char>(int count);

		inline const std::vector<VertexBufferElements> GetElements() const { return elements; }
		inline unsigned int GetStride() const { return stride; }
	};
}