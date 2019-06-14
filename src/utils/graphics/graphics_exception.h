#ifndef __GRAPHICS_EXCEPTION__
#define __GRAPHICS_EXCEPTION__
#include <exception>
#include <string>

namespace graphics
{
    class GraphicsException : public std::exception
    {
        const char * const message;
        public:
            GraphicsException(const char * msg)
                :message(msg)
            {
            }

			GraphicsException(const std::string & msg)
				:message(msg.c_str())
			{
			}

            const char * what() const noexcept override
            {
                return message;
            }
    };
}

#endif
