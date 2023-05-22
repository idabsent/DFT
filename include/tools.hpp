#pragma once

#include <common.hpp>
#include <complex>

namespace DFT
{

namespace tools
{

double operator ""_dgr(const char* radians, size_t len);
double degrees_to_radians(double radians);
std::complex<double> eiler_transformation(double pow, bool is_radians);
std::complex<double> calculate_right_part(size_t n, size_t m, size_t freq_count);
double amplitude(ft_value const& val);

}

}