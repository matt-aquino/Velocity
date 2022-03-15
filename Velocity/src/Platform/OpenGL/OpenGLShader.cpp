#include "vlpch.h"
#include "OpenGLShader.h"
#include "glm/gtc/type_ptr.hpp"

namespace Velocity
{
	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		// Create Vertex Shader
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* source = (const GLchar*)vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		glCompileShader(vertexShader);
		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);

		// log if compilation fails
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
			glDeleteShader(vertexShader);

			VL_CORE_ERROR("{0}", infoLog.data());
			VL_CORE_ASSERT(false, "Vertex shader failed to compile!");
			return;
		}

		// Create Fragment Shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		source = (const GLchar*)fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);

		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			VL_CORE_ERROR("{0}", infoLog.data());
			VL_CORE_ASSERT(false, "Fragment shader failed to compile!");
		}

		// Link Shaders into Program
		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);
		glLinkProgram(m_RendererID);

		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_RendererID);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			VL_CORE_ERROR("{0}", infoLog.data());
			VL_CORE_ASSERT(false, "Shader program failed to link!")
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
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