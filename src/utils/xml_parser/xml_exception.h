#ifndef __XML_PARSER_EXCEPTION__
#define __XML_PARSER_EXCEPTION__

#include <exception>
#include <string>

namespace xml
{
	class Tag;
    class XmlException : public std::exception
    {
        std::string message;
        public:
			XmlException(const xml::Tag * t);
			XmlException & NoProp(const std::string & prop_name);
			XmlException & NoChild(const std::string & child_name);
			XmlException & Messg(const std::string & msg);
            const char * what() const noexcept override;
    };
}

#endif
