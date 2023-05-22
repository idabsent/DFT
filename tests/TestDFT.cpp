#include <gtest/gtest.h>

#include <DFT.hpp>

#include <vector>
#include <complex>
#include <cmath>
#include <ranges>
#include <format>
#include <memory>
#include <utility>

template<size_t N>
double round_to(double num)
{
	auto pow_10 = std::pow(10, N);

	return std::round( num * pow_10 ) / pow_10;
}

template <typename T>
static std::string fmt_complex(std::complex<T> com)
{
	return std::format("{} {:+}j", com.real(), com.imag());
}

TEST(TestDFT, dft)
{
	std::vector<std::complex<double>> lefts{
		{15.0, 0.000},
		{-2.5, 3.441},
		{-2.5, 0.812},
		{-2.5, -0.812},
		{-2.5, -3.441},
	};

	std::vector<double> vals{ 
		1.0, 2.0, 3.0, 4.0, 5.0,
	};

	auto rights = DFT::dft(std::move(vals), (size_t) 5);
	auto range = std::views::iota((size_t) 0, std::min(lefts.size(), rights.size()));
	for (auto ind : range)
	{
		auto left = lefts.at(ind);
		auto right = rights.at(ind);
		right = { round_to<3>(right.real()), round_to<3>(right.imag()) };

		ASSERT_EQ(left, right) <<
			std::format("left must be equal to right. {} != {} | ind : {}",
				fmt_complex(left),
				fmt_complex(right),
				ind
			);
	}
}

TEST(TestDFT, DFT_amplitudes)
{
	std::vector<DFT::ret_value> lefts {
		{ 0.00, 0.000 },
		{ 15.0, 4.000 },
		{ 0.00, 2.000 },
		{ 0.00, 0.000 },
		{ 0.00, 0.000 },
		{ 0.00, 0.000 },
		{ 0.00, 2.000 },
		{ 0.00, 4.000 },
	};

	std::vector<double> vals {
		0.3535, 0.3535,
		0.6464, 1.0607,
		0.3535, -1.0607,
		-1.3535, -0.3535,
	};

	auto transformer = DFT::dft<std::vector<double>>;
	auto dft = DFT::DFT<std::vector<double>>(transformer, std::forward<std::vector<double>>(vals), (size_t) 7);
	auto dft_vals = transformer(std::forward<std::vector<double>>(vals), (size_t) 7);

	auto ampls = dft.amplitudes();
	
	auto range = std::views::iota((size_t) 0, ampls.size());
	for (auto ind : range)
	{
		auto [left_freq, left_ampl] = lefts.at(ind);
		auto [right_freq, right_ampl] = ampls.at(ind);

		ASSERT_EQ(round_to<3>(left_ampl), round_to<3>(right_ampl)) << 
			std::format("left must be equal to right. {} != {} | ind: {}",
				left_ampl, 
				right_ampl, 
				ind
			);
	}
}