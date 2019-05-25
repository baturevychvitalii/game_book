#ifndef __GRAPHICS_EXCEPTION__
#define __GRAPHICS_EXCEPTION__
#include <exception>

class GraphicsException : public std::exception
{
    const char * const message;
    public:
        GraphicsException(const char * msg)
            :message(msg)
        {
        }

        const char * what() const noexcept override
        {
            return message;
        }
};

#endif
