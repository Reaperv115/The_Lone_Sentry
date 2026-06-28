#include "gepch.h"
#include "VertexBuffer.h"

Engine::VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	Call(glGenBuffers(1, &id));
	Call(glBindBuffer(GL_ARRAY_BUFFER, id));
	Call(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

Engine::VertexBuffer::~VertexBuffer()
{

}

void Engine::VertexBuffer::Bind() const
{
	Call(glBindBuffer(GL_ARRAY_BUFFER, id));
}

void Engine::VertexBuffer::Unbind() const
{

}