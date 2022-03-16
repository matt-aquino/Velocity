#include "vlpch.h"
#include "OpenGLShader.h"
#include "glm/gtc/type_ptr.hpp"
#include <fstream>

namespace Velocity
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		VL_CORE_ASSERT(false, "Unknown shader type");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
	}
	
	OpenGLShader::OpenGLShader(const std::string& path)
	{
		std::string source = ReadFile(path);

		auto shaderSources = Preprocess(source);
		Compile(shaderSources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	std::string OpenGLShader::ReadFile(const std::string& file)
	{
		std::ifstream in(file, std::ios::in, std::ios::binary);
		std::string result;

		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}

		else
			VL_CORE_ERROR("Could not open file {0}", file);

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::Preprocess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			VL_CORE_ASSERT(eol != std::string::npos, "Syntax Error");

			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			VL_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type!");

			size_t nextLinePos = source.find_first_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, 
				pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(std::unordered_map<GLenum, std::string>& shaderSources)
	{
		GLuint program = glCreateProgram();
		std::vector<GLenum> shaderIDs(shaderSources.size());

		// compile all of our shaders
		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);
			const GLchar* src = (const GLchar*)source.c_str();
			glShaderSource(shader, 1, &src, 0);

			glCompileShader(shader);
			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
				glDeleteShader(shader);

				VL_CORE_ERROR("{0}", infoLog.data());
				VL_CORE_ASSERT(false, "Shader failed to compile!");
				break;
			}

			glAttachShader(program, shader);
			shaderIDs.push_back(shader);
		}		

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			for (auto& id : shaderIDs)
			{
				glDeleteShader(id);
			}

			VL_CORE_ERROR("{0}", infoLog.data());
			VL_CORE_ASSERT(false, "Shader program failed to link!");
			return;
		}

		for (auto& id : shaderIDs)
		{
			glDetachShader(program, id);
		}

		m_RendererID = program;
	}



	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::CheckIfUniformCached(const std::string& name)
	{
		if (m_UniformLocations.find(name) == m_UniformLocations.end())
		{
			GLint location = glGetUniformLocation(m_RendererID, name.c_str());
			m_UniformLocations[name] = location;
		}
	}

	// ====================== UNIFORMS ======================

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		CheckIfUniformCached(name);
		glUniformMatrix4fv(m_UniformLocations[name], 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		CheckIfUniformCached(name);
		glUniformMatrix3fv(m_UniformLocations[name], 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		CheckIfUniformCached(name);
		glUniform4fv(m_UniformLocations[name], 1, glm::value_ptr(values));
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values)
	{
		CheckIfUniformCached(name);
		glUniform3fv(m_UniformLocations[name], 1, glm::value_ptr(values));
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values)
	{
		CheckIfUniformCached(name);
		glUniform2fv(m_UniformLocations[name], 1, glm::value_ptr(values));
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, const float value)
	{
		CheckIfUniformCached(name);
		glUniform1fv(m_UniformLocations[name], 1, &value);
	}
	void OpenGLShader::UploadUniformInt(const std::string& name, const int value)
	{
		CheckIfUniformCached(name);
		glUniform1i(m_UniformLocations[name], value);
	}
}