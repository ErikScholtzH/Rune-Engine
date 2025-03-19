#pragma once

namespace Rune {
	class Texture {
	public:
		virtual ~Texture() = default;

		virtual void Bind(uint32_t slot = 0) const = 0;
		virtual void Unbind(uint32_t slot = 0) const = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

	private:
		uint32_t m_TextureID;

	};

	class Texture2D : public Texture {
	public:
		static Ref<Texture2D> Create(const std::string& path);
	};
}