#ifndef __UTILS_RNG__
#define __UTILS_RNG__

#include <random>

/**
Comfortable (for me) way to use RNG
*/
class RandomNumberGenerator
{
    private:
        std::random_device rd;
    public:
        RandomNumberGenerator() = default;
        RandomNumberGenerator(const RandomNumberGenerator & other) = delete;

		/*
		 * @return random value in range [from; to)
		 */
        int operator() (int from , int to);
};

#endif
