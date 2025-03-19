#pragma once

namespace Rune {

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static Ref<IndexBuffer>  Create(uint32_t* vertices, uint32_t size);
	};
}