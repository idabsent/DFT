#include <tools.hpp>
#include <common.hpp>

#include <cmath>
#include <cassert>
#include <numbers>
#include <string>
#include <cmath>

using namespace DFT;

static constexpr auto pi = std::numbers::pi;

double tools::degrees_to_radians(double radians)
{
	return radians * pi / 180.0;
}

double tools::operator ""_dgr(const char* radians, size_t len)
{
	return std::stod(std::string(radians, len));
}

std::complex<double> tools::eiler_transformation(double pow, bool is_radians)
{
	auto radians = is_radians ? pow : degrees_to_radians(pow);
	return std::complex<double> { std::cos(radians), -std::sin(radians) };
}

std::complex<double> tools::calculate_right_part(size_t n, size_t m, size_t freq_count)
{
	dft_assert(freq_count > 0, "freq_count must be greater then 0");
	auto pow = 2 * pi * n * m / freq_count;
	return eiler_transformation(pow, true);
}

double tools::amplitude(ft_value const& val)
{
	return std::sqrt(std::pow(val.imag(), 2) + std::pow(val.real(), 2));
}