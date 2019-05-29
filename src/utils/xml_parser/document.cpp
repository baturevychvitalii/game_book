#include "document.h"


xml::Document::Document(const std::string & filename)
 :file(filename)
{
    doc_ptr = xmlParseFile(file.c_str());
    if (doc_ptr == NULL)
        throw XmlException("couldn't parse doc with libxml2");
    
    root = xmlDocGetRootElement(doc_ptr);
}

xml::Document::Document(const std::string & filename, const std::string & root_name)
    : file(filename)
{
    doc_ptr = xmlNewDoc(BAD_CAST "1.0");
    root = xmlNewNode(NULL, BAD_CAST root_name.c_str());
    xmlDocSetRootElement(doc_ptr, root);
}

xml::Document::Document(const std::string & filename, xml::Tag & root_tag)
    : file(filename)
{
    doc_ptr = xmlNewDoc(BAD_CAST "1.0");
    root = root_tag.node;
    xmlDocSetRootElement(doc_ptr, root);
}

xml::Document::~Document()
{
    xmlFreeDoc(doc_ptr);
}

void xml::Document::Save(const char * filename) const
{
    if (!filename)
        filename = file.c_str();
    
    xmlSaveFile(filename, doc_ptr);
}

const xml::Tag xml::Document::Root() const
{
    return root;
}
