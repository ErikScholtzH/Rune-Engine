#include "rune_pch.h"

#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Rune {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type)
		{
		case Rune::ShaderDataType::Float:    return GL_FLOAT;
		case Rune::ShaderDataType::Float2:   return GL_FLOAT;
		case Rune::ShaderDataType::Float3:   return GL_FLOAT;
		case Rune::ShaderDataType::Float4:   return GL_FLOAT;
		case Rune::ShaderDataType::Mat3:     return GL_FLOAT;
		case Rune::ShaderDataType::Mat4:     return GL_FLOAT;
		case Rune::ShaderDataType::Int:      return GL_INT;
		case Rune::ShaderDataType::Int2:     return GL_INT;
		case Rune::ShaderDataType::Int3:     return GL_INT;
		case Rune::ShaderDataType::Int4:     return GL_INT;
		case Rune::ShaderDataType::Bool:     return GL_BOOL;
		}

		RUNE_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	};

	OpenGLVertexArray::OpenGLVertexArray() {
		RUNE_PROFILE_FUNCTION();
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		RUNE_PROFILE_FUNCTION();
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const {
		RUNE_PROFILE_FUNCTION();
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const {
		RUNE_PROFILE_FUNCTION();
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
		RUNE_PROFILE_FUNCTION();
		RUNE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();
		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();

		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
		RUNE_PROFILE_FUNCTION();
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
}