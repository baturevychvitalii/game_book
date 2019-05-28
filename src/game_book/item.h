#ifndef __GAMEBOOK_ITEM__
#define __GAMEBOOK_ITEM__


#include "../utils/interfaces/ISerializable.h"

class Item : ISerializable
{
    private:
        const std::string name;
        unsigned durability;
    public:
        Item(const xml::Tag & t);
        virtual ~Item();
        
        virtual void Use(size_t charges);
};

#endif
