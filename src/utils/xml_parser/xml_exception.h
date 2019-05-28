#ifndef __XML_PARSER_EXCEPTION__
#define __XML_PARSER_EXCEPTION__

#include <exception>

namespace xml
{
    class XmlException : public std::exception
    {
        const char * const message;
        public:
            XmlException(const char * msg)
                :message(msg)
            {
            }

            const char * what() const noexcept override
            {
                return message;
            }
    };
}

#endif
