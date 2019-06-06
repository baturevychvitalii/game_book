#ifndef __INTERFACE_SERIALIZABLE__
#define __INTERFACE_SERIALIZABLE__

#include "tag.h"

/**
can be understood from the name
*/
class ISerializable
{
    public:
        virtual xml::Tag Serialize() const = 0;
};

#endif
