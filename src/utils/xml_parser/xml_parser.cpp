#include "xml_parser.h"

xml_parser::Parser::Parser()
{
    LIBXML_TEST_VERSION
}

xml_parser::Parser::~Parser()
{
    xmlCleanupParser();
    xmlMemoryDump();
}

xml_parser::Document xml_parser::Parser::GetDoc(const std::string & filename)
{
    try
    {
        return Document(filename);
    }
    catch(...)
    {
        throw XmlException("couldn't load document");
    }
}

xml_parser::Document xml_parser::Parser::NewDoc(const std::string & filename, const std::string & root)
{
    return Document(filename, root);
}

xml_parser::Document xml_parser::Parser::NewDoc(const std::string & filename, xml_parser::Tag & root)
{
    return Document(filename, root);
}
