#include "gepch.h"
#include "Renderer.h"

Engine::Renderer::Renderer()
{
	OnInit();
}

void Engine::Renderer::Init()
{
	if (!instance)
		instance = CreateUnique<Renderer>();
}

Engine::Renderer::~Renderer()
{

}

void Engine::Renderer::PrepareGeometry()
{
	triangleCB = CreateUnique<ConstantBuffer>(sizeof(glm::mat4), 0);
	squareCB = CreateUnique<ConstantBuffer>(sizeof(glm::mat4), 1);

	// creating triangle primitive
	triangle = Primitives::Triangle();
	Primitives::Vertex v1, v2, v3;

	triangle.va = CreateUnique<VertexArray>();
	Primitives::Vertex trianglevertices[3] =
	{
		v1 = Primitives::Vertex( - 0.25f, -0.25f,  0.0f,	0.0f, 0.0f, 0.0f), // bottom left
		v2 = Primitives::Vertex(	0.0f,  0.25f,  0.0f,	0.5f, 1.0f, 0.0f), // top center
		v3 = Primitives::Vertex(	0.25f, -0.25f,  0.0f,	1.0f, 0.0f, 0.0f)  // bottom right

	};
	triangle.CalculateRadius(glm::vec3(v1.x, v1.y, v1.z), glm::vec3(v2.x, v2.y, v2.z), glm::vec3(v3.x, v3.y, v3.z));

	triangle.vbl = CreateUnique<VertexBufferLayout>();
	triangle.vbl->Push<float>(3);
	triangle.vbl->Push<float>(3);

	unsigned int triangleindices[3] =
	{
		0, 1, 2
	};

	triangle.va->Bind();
	triangle.vb = CreateUnique<VertexBuffer>(trianglevertices, sizeof(trianglevertices));
	triangle.va->AddVertexBuffer(*triangle.vb, *triangle.vbl);

	triangle.ib = CreateUnique<IndexBuffer>(triangleindices, 3);


	triangle.shader[ShaderUsage::color] = CreateUnique<Shader>("src/Shaders/TriangleColor.vert", "src/Shaders/TriangleColor.frag");
	//triangle.shader[ShaderUsage::geometry] = CreateUnique<Shader>("src/Shaders/TriangleGeomColor.vert", "src/Shaders/TriangleGeomColor.frag", "src/Shaders/TriangleGeomColor.geom");

	BindUniformBlock(triangle.shader[ShaderUsage::color]->GetID(), "CameraData");
	//BindUniformBlock(triangle.shader[ShaderUsage::geometry]->GetID(), "CameraData");

	// creating square primitive
	 square = Primitives::Square();
	 Primitives::Vertex sv1, sv2, sv3, sv4;

	square.va = CreateUnique<VertexArray>();
	Primitives::Vertex squarevertices[4] =
	{
		sv1 = Primitives::Vertex{  -0.25f, -0.25f,  0.0f,	1.0f, 0.65f, 0.0f},
		sv2 = Primitives::Vertex{  -0.25f,  0.25f,  0.0f,	1.0f, 0.65f, 0.0f},
		sv3 = Primitives::Vertex{	0.25f,  -0.25f, 0.0f,	1.0f, 0.65f, 0.0f},
		sv4 = Primitives::Vertex{	0.25f,  0.25f,  0.0f,   1.0f, 0.65f, 0.0f}

	};
	square.CalculateRadius(glm::vec3(sv1.x, sv1.y, sv1.z), glm::vec3(sv2.x, sv2.y, sv2.z), glm::vec3(sv3.x, sv3.y, sv3.z), glm::vec3(sv4.x, sv4.y, sv4.z));
	square.vbl = CreateUnique<VertexBufferLayout>();
	square.vbl->Push<float>(3);
	square.vbl->Push<float>(3);

	unsigned int squareindices[6] =
	{
		0, 1, 2,
		2, 1, 3
	};

	square.va->Bind();
	square.vb = CreateUnique<VertexBuffer>(squarevertices, sizeof(squarevertices));
	square.va->AddVertexBuffer(*square.vb, *square.vbl);

	square.ib = CreateUnique<IndexBuffer>(squareindices, 6);


	square.shaders[ShaderUsage::color] = CreateUnique<Shader>("src/Shaders/SquareColor.vert", "src/Shaders/SquareColor.frag");
	BindUniformBlock(square.shaders[ShaderUsage::color]->GetID(), "CameraData", 1);
}

void Engine::Renderer::BindUniformBlock(const unsigned int shaderid, const std::string& blockname, const unsigned int bindingslot)
{
	GLuint blockIndex = glGetUniformBlockIndex(shaderid, blockname.c_str());
	glUniformBlockBinding(shaderid, blockIndex, bindingslot);
}

void Engine::Renderer::OnInit()
{
	PrepareGeometry();
	camera = Camera();
}

#pragma region Triangles

void Engine::Renderer::DrawWeaponTriangleImpl(const glm::vec3& position, const float rotation, const float scale)
{
	glm::mat4x4 transform = glm::translate(glm::mat4(1.0f), position);
	transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, glm::vec3(scale, scale, scale));
	transform = camera.GetModelViewProjectionMatrix(transform);

	triangleCB->SetData(&transform, sizeof(glm::mat4), 0);
	triangleCB->Bind();

	triangle.shader[ShaderUsage::color]->Bind();
	triangle.va->Bind();
	triangle.ib->Bind();
	Call(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr))
}

void Engine::Renderer::DrawWeaponTriangle(const glm::vec3& position, const float rotation, const float scale)
{
	instance->DrawWeaponTriangleImpl(position, rotation, scale);
}

void Engine::Renderer::DrawTriangleImpl(const glm::vec3& position, const float rotation, const float scale)
{
	glm::mat4x4 transform = glm::translate(glm::mat4(1.0f), position);
	transform = glm::rotate(transform, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, glm::vec3(scale, scale, scale));
	transform = camera.GetModelViewProjectionMatrix(transform);

	triangleCB->SetData(&transform, sizeof(glm::mat4), 0);
	triangleCB->Bind();

	triangle.shader[ShaderUsage::color]->Bind();
	triangle.va->Bind();
	triangle.ib->Bind();
	Call(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr))
}
void Engine::Renderer::DrawTriangle(const glm::vec3& position, const float rotation, const float scale)
{
	instance->DrawTriangleImpl(position, rotation, scale);
}
#pragma endregion DrawingTriangles

#pragma region Squares

void Engine::Renderer::DrawSquare(const glm::vec3& position, const float rotation, const float scale)
{
	instance->DrawSquareImpl(position, rotation, scale);
}

void Engine::Renderer::DrawSquareImpl(const glm::vec3& position, const float rotation, const float scale)
{
	glm::mat4x4 transform = glm::translate(glm::mat4(1.0f), position);
	transform = glm::rotate(transform, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, glm::vec3(scale, scale, scale));
	transform = camera.GetModelViewProjectionMatrix(transform);

	squareCB->SetData(&transform, sizeof(glm::mat4));
	squareCB->Bind();

	square.shaders[ShaderUsage::color]->Bind();
	square.va->Bind();
	square.ib->Bind();
	Call(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr))
}


#pragma endregion Drawing squares


Engine::Unique<Engine::Renderer> Engine::Renderer::instance;