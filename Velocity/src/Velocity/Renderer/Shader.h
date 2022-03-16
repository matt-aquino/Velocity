#pragma once
#include <string>
#include "glm/glm.hpp"

namespace Velocity
{
	class Shader
	{
	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		// upload uniform matrices
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) = 0;

		// upload uniform vectors
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& values) = 0;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& values) = 0;
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& values) = 0;
		virtual void UploadUniformFloat(const std::string& name, const float value) = 0;


		virtual void UploadUniformInt(const std::string& name, const int value) = 0;

		static Shader* Create(std::string& vertSrc, std::string& fragSrc);
		static Shader* Create(const std::string& path);
	};
}