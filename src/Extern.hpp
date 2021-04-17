#pragma once

#include <cstdlib>
#include <functional>

inline std::function<void(void)> frameDraw;
extern std::size_t frameCount;

#pragma warning(suppress: 4455)
constexpr std::size_t operator"" z(unsigned long long n) noexcept
{
	return n;
}