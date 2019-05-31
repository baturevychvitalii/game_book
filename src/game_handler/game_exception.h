#ifndef __GAME_EXCEPTION__
#define __GAME_EXCEPTION__

#include <exception>

class GameException : public std::exception
{
    const char * const message;
    public:
        GameException(const char * msg)
            :message(msg)
        {
        }

        const char * what() const noexcept override
        {
            return message;
        }
};

#endif
