#include "rng.h"
#include "helpers.h"
#include <stdexcept>

int RandomNumberGenerator::operator()(int from, int to)
{
    if (from > to)
        throw std::invalid_argument("from > to");
    return from + (rd() % Distance(from, to));
}

