#pragma once
#include <memory>
#include "ErrorLogging.h"
using namespace ErrorLog;
#define BIT(x) (1 << x)
#define GE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define ASSERT(x) if (!(x)) __debugbreak();
#define Call(x) GetErrors();\
	x;\
	ASSERT(LogCall(#x, __FILE__, __LINE__))


namespace Engine
{
	template<typename T>
	using Unique = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Unique<T> CreateUnique(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Shared = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Shared<T> CreateShared(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
	
}

