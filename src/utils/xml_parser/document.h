#ifndef __XML_PARSER_DOCUMENT__
#define __XML_PARSER_DOCUMENT__

#include "tag.h";

namespace xml_parser
{
    class Document
    {
        const Tag root;
        const xmlDocPtr doc_ptr;
        
        public:
            Document(const std::string & filename);
            ~Document();
    };
}


#endif
