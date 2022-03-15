#pragma once
#include <string>
#include <unordered_map>
#include "glm/glm.hpp"
#include "Velocity/Renderer/Shader.h"

#include "glad/glad.h"
namespace Velocity
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;

		void CheckIfUniformCached(const std::string& name);

		// Uniform Upload functions
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) override;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& values) override;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& values) override;
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& values) override;
		virtual void UploadUniformFloat(const std::string& name, const float value) override;

	private:
		uint32_t m_RendererID;
		std::unordered_map<std::string, GLint> m_UniformLocations;
	};
}