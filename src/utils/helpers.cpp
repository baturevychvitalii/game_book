#include "helpers.h"

static char empty_chars[] = {' ', '\t', '\n', '\r'};

static bool IsEmptyChar(const char & ch)
{
    for (size_t i = 0; i < sizeof(empty_chars)/sizeof(char); i++)
    {
        if (empty_chars[i] == ch)
            return true;
    }

    return false;
}

static void AddWord(std::vector<std::string> & lines,
                    const std::string & word,
                    const unsigned & max_len)
{
    if (word.length() > max_len)
        throw std::invalid_argument("word is too long");

    if (lines.empty())
        lines.push_back(word);
    else
    {
        std::string & last_line = lines[lines.size() - 1];
        if (last_line.length() + 1 + word.length() > max_len)
        {
            lines.push_back(word);
        }
        else
        {
            last_line += ' ' + word;
        }
    }
}

size_t Distance(int a, int b) noexcept
{
    return a > b ? a - b : b - a;
}

size_t Intersection(int a1, int a2, int b1, int b2) noexcept
{
    if (a1 > a2)
        std::swap(a1,a2);
    if (b1 > b2)
        std::swap(b1,b2);

    int lowestMax = std::min(a2, b2), highestMin = std::max(a1,b1);
    if (highestMin > lowestMax)
        return 0;

    return Distance(lowestMax, highestMin);
}

unsigned MaxLength(const std::vector<std::string> & lines)
{
    if (lines.size() < 1)
        throw std::invalid_argument("empty lines");
    
    unsigned result = 0;
    for (const std::string & line : lines)
        result = line.length() > result ? line.length() : result;

    return result;
}

std::vector<std::string> BreakIntoLines(const std::string & text, unsigned max_width)
{
    std::vector<std::string> words(BreakIntoWords(text));
    std::vector<std::string> lines;
    lines.reserve(5);

    for (const std::string & word : words)
    {
        AddWord(lines, word, max_width);
    }

    return lines;
}

std::vector<std::string> BreakIntoWords(const std::string & text)
{
    std::vector<std::string> words;
    words.reserve(333);
    std::string word;
    for (const char & ch : text)
    {
        if (IsEmptyChar(ch))
        {
            if (word.length() > 0)
            {
                words.push_back(word);
                word = "";
            }

            continue;
        }

        word += ch;
    }

    if (word.length() > 0)
        words.push_back(word);

    return words;
}
