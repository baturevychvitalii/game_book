#ifndef __XML_PARSER_DOCUMENT__
#define __XML_PARSER_DOCUMENT__

#include "tag.h"

namespace xml
{
	/**
	holds an xml document and handlers to work with it
	(mainly through it's root tag)
	*/
    class Document
    {
        xmlDocPtr doc_ptr;
        xmlNodePtr root;
        const std::string file;
        public:
            Document(const std::string & filename);
            Document(const std::string & filename, const std::string & root);
            Document(const std::string & filename, Tag & root);
            ~Document();
            void Save(const char * filename = nullptr) const;
            const Tag Root() const;
    };
}


#endif
