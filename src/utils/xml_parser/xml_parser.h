#ifndef __XML_PARSER__
#define __XML_PARSER__

#include "document.h"

namespace xml
{
    class Parser final
    {
        public:
            Parser();
            ~Parser();

            static Document GetDoc(const std::string & name);
            static Document NewDoc(const std::string & name, const std::string & root);
            static Document NewDoc(const std::string & name, Tag & root);
    };
}

#endif
