#include "tag.h"

const char * xml_parser::Tag::textContentTagName = "text";

const char * xml_parser::Tag::XCharToNorm(const xmlChar * text)
{
    return reinterpret_cast<const char *>(text);
}

xml_parser::Tag::Tag(xmlNodePtr new_node)
    : node(new_node)
{
}

xml_parser::Tag::Tag(const std::string & name)
    : node(xmlNewNode(NULL, BAD_CAST name.c_str()))
{
}

xml_parser::Tag::Tag(const Tag & other)
    : node(other.node)
{
}

xml_parser::Tag & xml_parser::Tag::operator=(const Tag & other)
{
    this->node = other.node;
    return *this;
}

std::string xml_parser::Tag::Prop(const std::string & prop_name) const
{
    auto * found_prop = FindNodeStartingFrom(node->properties, prop_name);
    if (!found_prop)
        throw XmlException("attribute with requested name not found");
    
    return GetContent(found_prop);
}

void xml_parser::Tag::AddProp(const std::string & prop_name, const std::string & value)
{
    xmlNewProp(node, BAD_CAST prop_name.c_str(), BAD_CAST value.c_str());
}

xml_parser::Tag xml_parser::Tag::Child(const std::string & child_name) const
{
    auto * found_child = FindNodeStartingFrom(node->children, child_name);
    if (!found_child)
        throw XmlException("child with requested name not found");
    
    return found_child;
}

xml_parser::Tag xml_parser::Tag::AddChild(const std::string & child_name)
{
    return xmlAddChild(node, xmlNewNode(NULL, BAD_CAST child_name.c_str()));
}

void xml_parser::Tag::AddChild(const xml_parser::Tag & other)
{
    xmlAddChild(node, other.node);
}

xml_parser::Tag xml_parser::Tag::Next() const
{
    return FindNodeStartingFrom(node->next, Name());
}

std::vector<xml_parser::Tag> xml_parser::Tag::GetVector(const std::string & tag_name) const
{
    std::vector<Tag> tags;
    Tag found = Child(tag_name);
    while (found.Real())
    {
        tags.push_back(found);
        found = found.Next();
    }
    
    return tags;
}

bool xml_parser::Tag::Real() const
{
    return node != nullptr;
}

std::string xml_parser::Tag::Name() const
{
    return XCharToNorm(node->name);
}

std::string xml_parser::Tag::Text() const
{
    return GetContent(node);
}

void xml_parser::Tag::AddText(const std::string & text)
{
    xmlAddChild(node, xmlNewText(BAD_CAST text.c_str()));
}
