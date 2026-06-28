#include "gepch.h"
#include "Shader.h"

Engine::Shader::Shader(const std::string& vertexpath, const std::string& fragmentpath)
	: _id(0)
{
	LoadShader(vertexpath, fragmentpath);
}

Engine::Shader::~Shader()
{

}

unsigned int Engine::Shader::CreateShader(const std::string& vertexshader, const std::string& fragmentshader)
{
	Call(unsigned int program = glCreateProgram());
	Call(unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexshader));
	Call(unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentshader));
	

	Call(glAttachShader(program, vs));
	Call(glAttachShader(program, fs));
	Call(glLinkProgram(program));
	Call(glValidateProgram(program));

	Call(glDeleteShader(vs));
	Call(glDeleteShader(fs));

	return program;
}


unsigned int Engine::Shader::CompileShader(unsigned int type, const std::string& source)
{
	Call(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	Call(glShaderSource(id, 1, &src, nullptr));
	Call(glCompileShader(id));

	int result;
	Call(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		Call(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)_malloca(length + sizeof(char));
		Call(glGetShaderInfoLog(id, length, &length, message));
		switch (type)
		{
		case GL_VERTEX_SHADER:
			std::cout << "Failed to compile vertex shader!" << std::endl;
			break;
		case GL_FRAGMENT_SHADER:
			std::cout << "Failed to compile fragment shader!" << std::endl;
			break;
		case GL_GEOMETRY_SHADER:
			std::cout << "Failed to compile geometry shader!" << std::endl;
			break;
		}
		std::cout << message << std::endl;
		Call(glDeleteShader(id));
		return 0;
	}
	return id;
}

void Engine::Shader::LoadShader(const std::string& vertexpath, const std::string& fragmentpath)
{
	std::string vertexsource = ReadFile(vertexpath);
	std::string fragmentsource = ReadFile(fragmentpath);
	_id = CreateShader(vertexsource, fragmentsource);
}

std::string Engine::Shader::ReadFile(const std::string& filepath)
{
	std::ifstream stream(filepath);
	if (!stream.is_open())
	{
		std::cout << "Failed to open shader file: " << filepath.c_str() << std::endl;
		return "";
	}
	std::stringstream ss;
	ss << stream.rdbuf();
	return ss.str();
}

int Engine::Shader::GetUniformLocation(const std::string& name)
{
	if (uniformlocationCache.find(name) != uniformlocationCache.end())
		return uniformlocationCache[name];

	Call(unsigned int location = glGetUniformLocation(_id, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

	uniformlocationCache[name] = location;
	return location;
}

template<>
void Engine::Shader::SetUniform<float>(const std::string& name, const float& value)
{
	Call(glUniform1f(GetUniformLocation(name), value));
}

template<>
void Engine::Shader::SetUniform<int>(const std::string& name, const int& value)
{
	Call(glUniform1i(GetUniformLocation(name), value));
}

template<>
void Engine::Shader::SetUniform<glm::mat4>(const std::string& name, const glm::mat4& value)
{
	Call(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]));
}

void Engine::Shader::Bind() const
{
	Call(glUseProgram(_id));
}

void Engine::Shader::UnBind() const
{
	Call(glUseProgram(0));
}
