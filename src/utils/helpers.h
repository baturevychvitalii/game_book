#ifndef __UTILS_HELPERS__
#define __UTILS_HELPERS__
#include <vector>
#include <string>
#include <stdexcept>


size_t Distance(int a, int b) noexcept;
unsigned MaxLength(const std::vector<std::string> & lines);
std::vector<std::string> BreakIntoLines(const std::string & text, unsigned max_width);
std::vector<std::string> BreakIntoWords(const std::string & text);
size_t Intersection(int a1, int a2, int b1, int b2) noexcept;

#endif
