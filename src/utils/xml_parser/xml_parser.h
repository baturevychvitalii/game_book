#ifndef __XML_PARSER__
#define __XML_PARSER__

#include "document.h"

namespace xml_parser
{
    class Parser final
    {
        public:
            Parser();
            ~Parser();

            Document GetDoc(const std::string & name);
            Document NewDoc(const std::string & name, const std::string & root);
            Document NewDoc(const std::string & name, Tag & root);
    };
}

#endif
