#ifndef __UTILS_HELPERS__
#define __UTILS_HELPERS__
#include <vector>
#include <string>
#include <stdexcept>
#include "graphics/button.h"

/**
@return absolute distance between two values
*/
size_t Distance(int a, int b) noexcept;

/**
@return length of longest word in a text
*/
unsigned MaxLength(const std::vector<std::string> & lines);

/**
@return vector of lines, each of them is not longer than max_width
*/
std::vector<std::string> BreakIntoLines(const std::string & text, unsigned max_width);

/**
@return vector of words
*/
std::vector<std::string> BreakIntoWords(const std::string & text);

/**
@param a1 one point of first interval
@param a2 another point of first interval
@param b1 one point of second interval
@param b2 another point of second interval
@return intersection of two intervals
*/
size_t Intersection(int a1, int a2, int b1, int b2) noexcept;

#endif
