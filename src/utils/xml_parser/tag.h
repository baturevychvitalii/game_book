#ifndef __XML_PARSER_TAG__
#define __XML_PARSER_TAG__

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <string>
#include <vector>

#include "xml_exception.h"

namespace xml
{
	/**
	individual xml tag, which is comfortable to work with
	*/
    struct Tag
    {
		/**
		creates a tag in a libxml2 way
		*/
        Tag(xmlNodePtr new_node);

		/**
		creates an empty tag with a provided name
		*/
        Tag(const std::string & name);

		/**
		standard copy constructor
		*/
        Tag(const Tag & other);

		/**
		standard assignment operator
		*/
        Tag & operator=(const Tag & cp);
        ~Tag() = default;

		/**
		libxml2 representation
		*/
        xmlNodePtr node;

		/**
		@return name of a file, from which this tag was parsed if it was parsed from a file
		*/
        std::string GetFilename() const;

		/**
		get text value of a property with provided name
		*/
        std::string Prop(const std::string & prop_name) const;

		/**
		get child tag with a provided name
		*/
        Tag Child(const std::string & child_name) const;

		/**
		@return next child with same name under same parent node
		*/
        Tag Next() const;

		/**
		@return child tags with provided name in a vector
		*/
        std::vector<Tag> GetVector(const std::string & tag_name) const;

		/**
		@return name of this tag
		*/
        std::string Name() const;

		/**
		@return text content of this tag
		*/
        std::string Text() const;

		/**
		tells if this node is real or i's just signaling about the branch end
		*/
        bool IsNull() const;
        
		/**
		add property to this tag
		@param prop_name name of a property
		@param value value of a property
		*/
        Tag & AddProp(const std::string & prop_name, const std::string & value);

		/**
		adds text content to this tag
		*/
        Tag & AddText(const std::string & text);

		/**
		add child to this node
		*/
        Tag AddChild(const Tag & other);

		/**
		add child with provided name
		NOTE: probably no need in this function because there is an implicit constructor
		*/
        Tag AddChild(const std::string & child_name);

		/**
		adds property, converts it's value to string if possible
		*/
		template<typename ToStringable>
		Tag & AddProp(const std::string & prop_name, const ToStringable & value)
		{
			return AddProp(prop_name, std::to_string(value));
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
