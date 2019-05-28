#ifndef __INTERFACE_SERIALIZABLE__
#define __INTERFACE_SERIALIZABLE__

#include "../xml_parser/tag.h"

class ISerializable
{
    public:
        virtual xml::Tag Serialize() const = 0;
};

#endif
