#pragma once
#include "Rune/Renderer/Shader.h"

#include <string>

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace Rune {

	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadUniformBool(const std::string& name, bool value) override;
		virtual void UploadUniformInt(const std::string& name, int value) override;
		virtual void UploadUniformFloat(const std::string& name, float value) override;
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2 value) override;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3 value) override;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4 value) override;
		virtual void UploadUniformMat3(const std::string& name, const glm::mat3 matrix) override;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4 matrix) override;

	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

		uint32_t m_RendererID;
	};
}