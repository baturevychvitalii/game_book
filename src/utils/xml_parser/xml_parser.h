#ifndef __XML_PARSER__
#define __XML_PARSER__

#include <unordered_map>

#include "document.h"

namespace xml_parser
{
    class Parser final
    {
        std::unordered_map<std::string, Document> loaded_docs;
        public:
            Parser();
            ~Parser();

            const Document & ParseDoc(const std::string & filename);
            const Document & GetDoc(const std::string & name);
    };
}

#endif
