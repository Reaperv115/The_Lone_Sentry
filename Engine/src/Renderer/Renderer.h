#pragma once
#include "Primitives.h"
#include "Camera/Camera.h"
#include "Shaders/Shader.h"
#include "ConstantBuffer.h"
#include "Core.h"
#include "Textures/Texture.h"
#include "Transform.h"

namespace Engine
{
	enum ShaderUsage
	{
		color = 0,
		geometry
	};

	class Renderer
	{
	public:
		Renderer();
		~Renderer();
		static void Init();

		void PrepareGeometry();
		void BindUniformBlock(const unsigned int shaderid, const std::string& blockname, const unsigned int bindingslot = 0);

		void OnInit();

		// triangle
		void DrawTriangleImpl(const glm::vec3& position, const float rotation, const float scale);
		static void DrawTriangle(const glm::vec3& position, const float rotation, const float scale);

		void DrawWeaponTriangleImpl(const glm::vec3& position, const float rotation, const float scale);
		static void DrawWeaponTriangle(const glm::vec3& position, const float rotation, const float scale);

		// square
		void DrawSquareImpl(const glm::vec3& position);
		static void DrawSquare(const glm::vec3& position);

		void DrawSquareImpl(const glm::vec3& position, const float rotation, const float scale);
		static void DrawSquare(const glm::vec3& position, const float rotation, const float scale);

	private:
		static Unique<Renderer> instance;
		Primitives::Triangle triangle;
		Primitives::Square square;
		Camera camera;
		Unique<ConstantBuffer> triangleCB;
		Unique<ConstantBuffer> squareCB;
	};
}

