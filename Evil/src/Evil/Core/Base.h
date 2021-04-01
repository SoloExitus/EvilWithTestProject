#pragma once

#include <memory>

#include "Evil/Core/PlatformDetection.h"

#ifdef EVIL_DEBUG
	#if defined(EVIL_PLATFORM_WINDOWS)
		#define EVIL_DEBUGBREAK() __debugbreak()
	#elif defined(EVIL_PLATFORM_LINUX)
		#include <signal.h>
		#define EVIL_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define EVIL_ENABLE_ASSERTS
#else
	#define EVIL_DEBUGBREAK()
#endif // EVIL_DEBUG

// TODO: Make this macro able to take in no arguments except condition
#ifdef EVIL_ENABLE_ASSERTS
#define EVIL_ASSERT(x, ...) { if(!(x)) { EVIL_ERROR("Assertion Failed: {0}", __VA_ARGS__); EVIL_DEBUGBREAK(); } }
#define EVIL_CORE_ASSERT(x, ...) { if(!(x)) { EVIL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); EVIL_DEBUGBREAK(); } }
#else
	#define EVIL_ASSERT(x, ...)
	#define EVIL_CORE_ASSERT(x, ...)
#endif //EVIL_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define EVIL_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Evil
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template <typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
	
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template <typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
