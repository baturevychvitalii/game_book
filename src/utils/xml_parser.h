#ifndef __XML_PARSER__
#define __XML_PARSER__

#include <libxml/parser.h>
#include <libxml/tree.h>


 const class XmlParser final
{
    public:
        struct Tag
        {
            Tag(xmlNodePtr new_node)
                :node(new_node)
            {
            }

            Tag(const Tag & other) = default;
            ~Tag() = default;
            Tag &       operator=       (Tag cp);

            const xmlNodePtr node;

            std::string ValueOfAttribute(const std::string & attr_name) const;
            std::string operator[]      (const std::string & attr_name) const;

            const Tag   GetChild        (const std::string & child_name) const;
            const Tag   operator()      (const std::string & child_name) const;

            std::string Text            () const;
        };

    private:
        const xmlDocPtr document;
        Tag root;

    public:
        XmlParser(const char * filename);
        ~XmlParser();
};

XmlParser::XmlParser(const char * filename)
    : document(xmlParseFile(filename)), root(xmlDocGetRootElement(document))
{
}

XmlParser::~XmlParser()
{
    xmlFreeDoc(document);
}

#endif
