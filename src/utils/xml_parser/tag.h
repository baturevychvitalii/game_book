#ifndef __XML_PARSER_TAG__
#define __XML_PARSER_TAG__

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <string>

namespace xml_parser
{
    struct Tag
    {
        Tag(xmlNodePtr new_node)
            :node(new_node)
        {
        }

        Tag(const Tag & other) = default;
        ~Tag() = default;
        Tag & operator=(Tag cp);

        const xmlNodePtr node;

        std::string ValueOfAttribute(const std::string & attr_name) const;
        std::string operator[]      (const std::string & attr_name) const;

        const Tag   GetChild        (const std::string & child_name) const;
        const Tag   operator()      (const std::string & child_name) const;

        std::string Text() const;
    };
}

#endif
