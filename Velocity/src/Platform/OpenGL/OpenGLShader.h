#pragma once
#include "glm/glm.hpp"
#include "Velocity/Renderer/Shader.h"

#include "glad/glad.h"
namespace Velocity
{
	class OpenGLShader : public Shader
	{
	public:
		/// <summary>
		/// Create a shader program using 2 separate strings 
		/// </summary>
		/// <param name="vertSrc">string containing vertex shader code</param>
		/// <param name="fragSrc">string containing fragment shader code</param>
		/// <returns></returns>
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

		/// <summary>
		/// Create a shader program by passing in a .glsl file path
		/// </summary>
		/// <param name="path">the location of the .glsl file</param>
		/// <returns></returns>
		OpenGLShader(const std::string& path);
		~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;

		void CheckIfUniformCached(const std::string& name);
		virtual const std::string& GetName() const override { return m_Name; }

		// Uniform Upload functions
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) override;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& values) override;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& values) override;
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& values) override;
		virtual void UploadUniformFloat(const std::string& name, const float value) override;
		virtual void UploadUniformInt(const std::string& name, const int value) override;

	private:
		std::string ReadFile(const std::string& file);
		std::unordered_map<GLenum, std::string> Preprocess(const std::string& source);
		void Compile(std::unordered_map<GLenum, std::string>& shaderSources);

		uint32_t m_RendererID;
		std::unordered_map<std::string, GLint> m_UniformLocations;
		std::string m_Name;
	};
}