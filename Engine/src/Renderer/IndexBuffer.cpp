#include "gepch.h"
#include "IndexBuffer.h"

Engine::IndexBuffer::IndexBuffer(const unsigned int* data, const unsigned int indexcount)
	:id(0), indexCount(indexcount)
{
	Call(glGenBuffers(1, &id));
	Call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
	Call(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexcount * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

Engine::IndexBuffer::~IndexBuffer()
{
	Call(glDeleteBuffers(1, &id));
}

void Engine::IndexBuffer::Bind() const
{
	Call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
}

void Engine::IndexBuffer::Unbind() const
{
	Call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

