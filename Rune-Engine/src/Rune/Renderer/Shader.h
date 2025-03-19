#pragma once

#include <string>

#include <glm/glm.hpp>

namespace Rune {

	class Shader {
	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void UploadUniformBool(const std::string& name, bool value) = 0;
		virtual void UploadUniformInt(const std::string& name, int value) = 0;
		virtual void UploadUniformFloat(const std::string& name, float value) = 0;
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2 value) = 0;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3 value) = 0;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4 value) = 0;
		virtual void UploadUniformMat3(const std::string& name, const glm::mat3 value) = 0;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4 value) = 0;
		
		
		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	private:
		uint32_t m_RendererID;
	};
}