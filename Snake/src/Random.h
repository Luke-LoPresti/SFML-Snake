/**
 * @file Random.cpp
 *
 * @brief Header file for Random class. Utility class to generate random numbers
 *		  using a Mersenne Twister 19937 generator.
 *
 * @author Luke Lo Presti
 * Date: 23-Oct-2020
 *
 */

#pragma once
#include <random>

namespace utility
{

class Random
{
public:
	Random();
	Random(const std::mt19937& seed);

	int getRandomNumber(int min, int max);

private:
	std::mt19937 mRng;
};

} // namespace utility
