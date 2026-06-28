#include "gepch.h"
#include "ConstantBuffer.h"

Engine::ConstantBuffer::ConstantBuffer(unsigned int size, unsigned int bindingslot)
	:id(0), slot(bindingslot)
{
	Call(glGenBuffers(1, &id));
	Call(glBindBuffer(GL_UNIFORM_BUFFER, id));
	Call(glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
	Call(glBindBufferBase(GL_UNIFORM_BUFFER, bindingslot, id));
	Call(glBindBuffer(GL_UNIFORM_BUFFER, 0));
}

Engine::ConstantBuffer::~ConstantBuffer()
{
	Call(glDeleteBuffers(1, &id));
}

void Engine::ConstantBuffer::Bind() const
{
	Call(glBindBufferBase(GL_UNIFORM_BUFFER, slot, id));
}

void Engine::ConstantBuffer::UnBind() const
{
	Call(glBindBuffer(GL_UNIFORM_BUFFER, 0));
}

void Engine::ConstantBuffer::SetData(const void* data, unsigned int size, unsigned int offset /*= 0*/)
{
	Call(glBindBuffer(GL_UNIFORM_BUFFER, id));
	Call(glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data));
	Call(glBindBuffer(GL_UNIFORM_BUFFER, 0));
}