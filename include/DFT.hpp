// DFT.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <vector>
#include <string>
#include <utility>
#include <complex>
#include <ranges>
#include <common.hpp>
#include <tools.hpp>
#include <iostream>
#include <ranges>
#include <algorithm>
#include <utility>
#include <numeric>
#include <numbers>
#include <execution>
#include <complex>
#include <cmath>

namespace
{
	std::vector<double> freqs(size_t freq_count, size_t point_count)
	{
		double freq = static_cast<double>(freq_count / point_count);
		std::vector<double> frequentes; frequentes.reserve(point_count);
		for (auto const& i : std::views::iota((size_t) 0, point_count))
		{
			frequentes.push_back(i * freq);
		}
		return frequentes;
	}
}

namespace DFT{

template<typename Args>
std::vector<ft_value> dft(Args && args, size_t point_count)
{
	std::vector<std::complex<double>> vals; vals.reserve(point_count);
	auto points_range = std::views::iota((size_t)0, point_count);
	for (const auto& point_ind : points_range)
	{
		auto freqs_range = std::views::iota((size_t)0, args.size());
		std::complex<double> complex_ampl;
		for (const auto& freq_ind : freqs_range)
		{
			const auto freq = args.at(freq_ind);
			complex_ampl += freq * DFT::tools::calculate_right_part(freq_ind, point_ind, args.size());
		}
		vals.push_back(complex_ampl);
	}

	return vals;
}

template<typename Args>
std::vector<ft_value> fft(Args && args, size_t point_count)
{

}

template<typename Vals>
struct DFT 
{
	DFT(ft<Vals> transformer, Vals && args, size_t point_count);

	std::vector<ret_value> amplitudes() const;

private:
	std::vector<ft_value> ft_vals;
	std::vector<double> freqs;
	size_t point_count;
};

template<typename Vals>
DFT<Vals>::DFT(ft<Vals> transformer, Vals && args, size_t point_count)
	:ft_vals{transformer(std::move(args), point_count)}
	,freqs{::freqs(args.size(), point_count)}
	,point_count{point_count}
{	}

template<typename Vals>
std::vector<ret_value> DFT<Vals>::amplitudes() const 
{
	std::vector<ret_value> result; result.reserve(point_count);

	auto range = std::views::iota((size_t) 0, point_count);
	for (auto ind : range)
	{
		auto freq = freqs.at(ind);
		auto val = ft_vals.at(ind);
		auto ampl = tools::amplitude(val);

		result.push_back(std::pair{freq, ampl});
	}

	return result;
}

std::string library_version();
std::string library_description();

}

// TODO: Reference additional headers your program requires here.
