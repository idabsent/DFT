#include <gtest/gtest.h>

#include <complex>
#include <ranges>
#include <algorithm>
#include <format>
#include <numeric>

#include <tools.hpp>

template <typename T>
static std::string fmt_complex(std::complex<T> com)
{
	return std::format("{} {:+}j", com.real(), com.imag());
}

TEST(TestTools, test_eiler_transformation)
{
	std::vector<double> radians{ 0.0, 90.0, 180.0, 270.0, 360.0 };

	std::vector<std::complex<double>> lefts{
		{1.0, 0.0},
		{0.0, -1.0},
		{-1.0, 0.0},
		{0.0, 1.0},
		{1.0, 0.0},
	};

	auto range = std::views::iota((size_t)0, std::min(lefts.size(), radians.size()));
	for (auto ind : range)
	{
		auto left = lefts.at(ind);
		auto right = DFT::tools::eiler_transformation(radians.at(ind), false);
		right = { std::round(right.real()), std::round(right.imag()) };

		ASSERT_EQ(left, right) 
			<< std::format("left must be equal to right. {} != {} for {}", fmt_complex(left), fmt_complex(right), radians.at(ind));
	}
}

TEST(TestTools, test_calculate_right_part)
{
	std::vector<std::complex<double>> lefts {
		{ 	1.0, 	0.0 },
		{  -1.0, 	0.0 },
		{   0.0,   -1.0 },
	};

	std::vector<std::tuple<size_t, size_t, size_t>> args {
		{0, 0, 1},
		{1, 2, 4},
		{1, 1, 4},
	};

	auto range = std::views::iota((size_t) 0, std::min(lefts.size(), args.size()));
	for (auto ind : range)
	{
		auto [n, m, freq_count] = args.at(ind);
		auto right = DFT::tools::calculate_right_part(n, m, freq_count);
		right = { std::round(right.real()), std::round(right.imag()) };
		auto left = lefts.at(ind);

		ASSERT_EQ(left, right) <<
			std::format("left must be equal to right. {} != {} for args ({}, {}, {})",
				fmt_complex(left),
				fmt_complex(right),
				n, m, freq_count
			);
	}
}

TEST(TestTools, panic_calculate_right_part)
{
	EXPECT_DEATH(DFT::tools::calculate_right_part(1,1,0), "freq_count must be greater then 0");
}