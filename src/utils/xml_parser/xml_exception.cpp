#include "xml_exception.h"
#include "tag.h"

xml::XmlException::XmlException(const xml::Tag * t)
	:message("in tag " + t->Name() + " ")
{
}

xml::XmlException & xml::XmlException::NoProp(const std::string & prop_name)
{
	message += "couldn't find Property " + prop_name;
	return *this;
}

xml::XmlException & xml::XmlException::NoChild(const std::string & child_name)
{
	message += "couldn't find Child " + child_name;
	return *this;
}

xml::XmlException & xml::XmlException::Messg(const std::string & msg)
{
	message += msg;
	return *this;
}

const char * xml::XmlException::what() const noexcept
{
	return message.c_str();
}
