#pragma once

#include <memory>

#ifdef RUNE_PLATFORM_WINDOWS // TODO this macro does not exist yet
	#ifdef RUNE_BUILD_DLL
		#define RUNE_API __declspec(dllexport)
	#else 
		#define RUNE_API __declspec(dllimport)
	#endif
#else
	#error Rune is only currently supported on windows
#endif

#ifdef RUNE_ENABLE_ASSERTS
	#define RUNE_ASSERT(x, ...) { if(!(x)) { RUNE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define RUNE_CORE_ASSERT(x, ...) { if(!(x)) { RUNE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define RUNE_ASSERT(x, ...)
	#define RUNE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define RUNE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)


namespace Rune {

	template <typename T>
	using Ref = std::shared_ptr<T>; // Reference counted pointer

	template <typename T>
	using Scope = std::unique_ptr<T>; // Scoped pointer

	template <typename T>
	using Weak = std::weak_ptr<T>; // Weak pointer

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args){
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}
