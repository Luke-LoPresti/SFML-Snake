/**
 * @file Random.cpp
 *
 * @brief Implementation of Random class. Utility class to generate random numbers
 *		  using a Mersenne Twister 19937 generator.
 *
 * @author Luke Lo Presti
 * Date: 23-Oct-2020
 *
 */

#include "Random.h"

namespace utility
{

Random::Random()
{
	std::random_device rd;
	mRng = std::mt19937(rd());
}

Random::Random(const std::mt19937& seed)
	: mRng(seed)
{
}

int Random::getRandomNumber(int min, int max)
{
	return std::uniform_int_distribution<std::mt19937::result_type>(min, max)(mRng);
}

}
