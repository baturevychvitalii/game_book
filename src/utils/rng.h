#ifndef __UTILS_RNG__
#define __UTILS_RNG__

#include <random>

class RandomNumberGenerator
{
    private:
        std::random_device rd;
    public:
        RandomNumberGenerator() = default;
        RandomNumberGenerator(const RandomNumberGenerator & other) = delete;
        int operator() (int from , int to);
};

#endif
