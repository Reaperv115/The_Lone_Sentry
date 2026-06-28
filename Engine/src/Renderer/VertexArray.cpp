#include "gepch.h"
#include "VertexArray.h"

Engine::VertexArray::VertexArray()
	:id(0)
{
	Call(glCreateVertexArrays(1, &id));
}

Engine::VertexArray::~VertexArray()
{
	Call(glDeleteVertexArrays(1, &id));
}

void Engine::VertexArray::Bind()
{
	Call(glBindVertexArray(id));
}

void Engine::VertexArray::UnBind()
{
	Call(glBindVertexArray(0));
}

void Engine::VertexArray::AddVertexBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		Call(glEnableVertexAttribArray(i));
		Call(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElements::GetSizeOfType(element.type);
	}
}

void Engine::VertexArray::AddIndexBuffer(const IndexBuffer& ib)
{
	Bind();
	ib.Bind();
}
