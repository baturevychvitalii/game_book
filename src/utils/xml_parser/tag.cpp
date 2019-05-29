#include "tag.h"

const char * xml::Tag::textContentTagName = "text";

const char * xml::Tag::XCharToNorm(const xmlChar * text)
{
    return reinterpret_cast<const char *>(text);
}

xml::Tag::Tag(xmlNodePtr new_node)
    : node(new_node)
{
}

xml::Tag::Tag(const std::string & name)
    : node(xmlNewNode(NULL, BAD_CAST name.c_str()))
{
}

xml::Tag::Tag(const Tag & other)
    : node(other.node)
{
}

xml::Tag & xml::Tag::operator=(const Tag & other)
{
    this->node = other.node;
    return *this;
}

std::string xml::Tag::Prop(const std::string & prop_name) const
{
    auto * found_prop = FindNodeStartingFrom(node->properties, prop_name);
    if (!found_prop)
        throw XmlException("attribute with requested name not found");
    
    return GetContent(found_prop);
}

xml::Tag & xml::Tag::AddProp(const std::string & prop_name, const std::string & value)
{
    xmlNewProp(node, BAD_CAST prop_name.c_str(), BAD_CAST value.c_str());
    return *this;
}

xml::Tag xml::Tag::Child(const std::string & child_name) const
{
    auto * found_child = FindNodeStartingFrom(node->children, child_name);
    if (!found_child)
        throw XmlException("child with requested name not found");
    
    return found_child;
}

xml::Tag xml::Tag::AddChild(const std::string & child_name)
{
    return xmlAddChild(node, xmlNewNode(NULL, BAD_CAST child_name.c_str()));
}

xml::Tag xml::Tag::AddChild(const xml::Tag & other)
{
    return xmlAddChild(node, other.node);
}

xml::Tag xml::Tag::Next() const
{
    return FindNodeStartingFrom(node->next, Name());
}

std::vector<xml::Tag> xml::Tag::GetVector(const std::string & tag_name) const
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

bool xml::Tag::Real() const
{
    return node != nullptr;
}

std::string xml::Tag::Name() const
{
    return XCharToNorm(node->name);
}

std::string xml::Tag::Text() const
{
    return GetContent(node);
}

void xml::Tag::AddText(const std::string & text)
{
    xmlAddChild(node, xmlNewText(BAD_CAST text.c_str()));
}
