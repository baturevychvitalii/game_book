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

        std::string Prop(const std::string & prop_name) const;
        void AddProp(const std::string & prop_name, const std::string & value);
        Tag Child(const std::string & child_name) const;
        Tag AddChild(const std::string & child_name);
        void AddChild(const Tag & other);
        Tag Next() const;
        std::vector<Tag> GetVector(const std::string & tag_name) const;
        std::string Name() const;
        std::string Text() const;
        void AddText(const std::string & text);
        bool Real() const;

        template<typename T>
        static T Deserialize(const Tag & tag)
        {
            return T(tag);
        }

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
