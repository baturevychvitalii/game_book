#include "xml_parser.h"

xml::Parser::Parser()
{
	LIBXML_TEST_VERSION
}

xml::Parser::~Parser()
{
	xmlCleanupParser();
	xmlMemoryDump();
}

xml::Document xml::Parser::GetDoc(const std::string & filename)
{
	return Document(filename);
}

xml::Document xml::Parser::NewDoc(const std::string & filename, const std::string & root)
{
	return Document(filename, root);
}

xml::Document xml::Parser::NewDoc(const std::string & filename, xml::Tag & root)
{
	return Document(filename, root);
}
