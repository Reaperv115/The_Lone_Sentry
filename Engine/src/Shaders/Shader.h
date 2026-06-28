#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include "Core.h"
#include "glm/glm.hpp"
#include <unordered_map>

namespace Engine
{
	struct ShaderProgramSource
	{
		std::string vertexsource, fragmentsource;
	};

	class Shader
	{
	public:
		Shader(const std::string& vertexpath, const std::string& fragmentpath);
		~Shader();

		unsigned int CreateShader(const std::string& vertexshader, const std::string& fragmentshader);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		ShaderProgramSource ParseShader(const std::string& filepath);
		void LoadShader(const std::string& vertexpath, const std::string& fragmentpath);
		static std::string ReadFile(const std::string& filepath);
		int GetUniformLocation(const std::string& name);

		template<typename T>
		void SetUniform(const std::string& name, const T& value);

		void Bind() const;
		void UnBind() const;

		unsigned int GetID() const { return _id; }
		unsigned int GetGeomID() const { return geomid; }
	private:
		std::string filepath;
		unsigned int _id;
		unsigned int geomid;
		std::unordered_map<std::string, int> uniformlocationCache;
	};
}

