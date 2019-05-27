#include "xml_parser.h"

static const char * textContent = "text";

xml_parser::Parser::Parser()
{
    LIBXML_TEST_VERSION
}

xml_parser::Parser::~Parser()
{
    xmlCleanupParser();
    xmlMemoryDump();
}
