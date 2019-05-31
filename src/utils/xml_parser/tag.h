#ifndef __XML_PARSER_TAG__
#define __XML_PARSER_TAG__

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <string>
#include <vector>

#include "xml_exception.h"

namespace xml
{
    struct Tag
    {
        Tag(xmlNodePtr new_node);
        Tag(const std::string & name);
        Tag(const Tag & other);
        Tag & operator=(const Tag & cp);
        ~Tag() = default;

        xmlNodePtr node;

        std::string GetFilename() const;
        std::string Prop(const std::string & prop_name) const;
        Tag Child(const std::string & child_name) const;
        Tag Next() const;
        std::vector<Tag> GetVector(const std::string & tag_name) const;
        std::string Name() const;
        std::string Text() const;
        bool IsNull() const;
        
        Tag & AddProp(const std::string & prop_name, const std::string & value);
        Tag & AddText(const std::string & text);
        Tag AddChild(const Tag & other);
        Tag AddChild(const std::string & child_name);


        private:
            static const char * textContentTagName;

            static const char * XCharToNorm(const xmlChar * text);

            template<typename NodePtr>
            static NodePtr FindNodeStartingFrom(NodePtr first, const std::string & name)
            {
                const xmlChar * looking_for = reinterpret_cast<const xmlChar *>(name.c_str());
                while (first != NULL)
                {
                    if (!xmlStrcmp(first->name, looking_for))
                        return first;

                    first = first->next;
                }

                return nullptr;
            }

            template<typename NodePtr>
            static const char * GetContent(NodePtr node)
            {
                auto * proper_child = FindNodeStartingFrom(node->children, textContentTagName);
                return XCharToNorm(proper_child->content);
            }
    };
}

#endif
