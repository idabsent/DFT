#pragma once

#include <functional>
#include <vector>
#include <complex>

#ifdef _WIN32
#	define DFT_SIGN __FUNCSIG__
#elif defined(__linux__)
#	define DFT_SIGN __PRETTY_FUNCTION__
#endif

#define dft_assert(condition, msg) \
	assert((condition) && (DFT_SIGN ": " msg))

namespace DFT
{

inline namespace common
{

using ft_value = std::complex<double>;
using ret_value = std::pair<double, double>;

template <typename Args>
using ft = std::function<std::vector<ft_value>(Args && args, size_t)>;


} // namespace common

}