#include "gepch.h"
#include "VertexBufferLayout.h"

template<>
void Engine::VertexBufferLayout::Push<float>(int count)
{
	VertexBufferElements vbe;
	vbe.count = count;
	vbe.type = GL_FLOAT;
	vbe.normalized = GL_FALSE;
	elements.push_back(vbe);
	stride += count * sizeof(float);
}

template<>
void Engine::VertexBufferLayout::Push<unsigned int>(int count)
{
	VertexBufferElements vbe;
	vbe.count = count;
	vbe.type = GL_UNSIGNED_INT;
	vbe.normalized = GL_FALSE;
	elements.push_back(vbe);
	stride += count * sizeof(unsigned int);
}

template<>
void Engine::VertexBufferLayout::Push<unsigned char>(int count)
{
	VertexBufferElements vbe;
	vbe.count = count;
	vbe.type = GL_UNSIGNED_BYTE;
	vbe.normalized = GL_FALSE;
	elements.push_back(vbe);
	stride += count * sizeof(char);
}