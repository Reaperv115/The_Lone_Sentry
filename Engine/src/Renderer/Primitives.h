#pragma once
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "glm/glm.hpp"
#include "Core.h"
#include "Shaders/Shader.h"
#include "Textures/Texture.h"

namespace Primitives
{
	struct Vertex
	{
		float x, y, z;
		float r, g, b;

		Vertex(){}

		Vertex(float x, float y, float z, float r, float g, float b)
			: x(x), y(y), z(z), r(r), g(g), b(b){}
	};

	struct Triangle
	{

		Engine::Unique<Engine::VertexArray> va;
		Engine::Unique<Engine::VertexBuffer> vb;
		Engine::Unique<Engine::IndexBuffer> ib;
		Engine::Unique<Engine::VertexBufferLayout> vbl;
		Engine::Unique<Engine::Shader> shader[3] = { nullptr, nullptr, nullptr };
		Engine::Unique<Engine::Texture> texture;
		
		inline static float radius;


		void CalculateRadius(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3)
		{
			glm::vec3 center = (v1 + v2 + v3) / 3.0f;
			radius = glm::distance(v1, center);
		}
		static inline float GetRadius() { return radius; }
	};

	struct Square
	{
		Engine::Unique<Engine::VertexArray> va;
		Engine::Unique<Engine::VertexBuffer> vb;
		Engine::Unique<Engine::IndexBuffer> ib;
		Engine::Unique<Engine::VertexBufferLayout> vbl;
		Engine::Unique<Engine::Shader> shaders[3] = { nullptr, nullptr, nullptr };
		Engine::Unique<Engine::Texture> texture;

		inline static float radius;

		void CalculateRadius(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const glm::vec3& v4)
		{
			glm::vec3 center = (v1 + v2 + v3 + v4) / 4.0f;
			radius = glm::distance(v1, center);
		}
		static inline float GetRadius() { return radius; }
	};
}