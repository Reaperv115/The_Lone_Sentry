#pragma once
#include "Core.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

namespace Engine
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind();
		void UnBind();

		void AddVertexBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
		void AddIndexBuffer(const IndexBuffer& ib);

	private:
		unsigned int id;
	};
}