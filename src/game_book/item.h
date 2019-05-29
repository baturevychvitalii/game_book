#ifndef __GAMEBOOK_ITEM__
#define __GAMEBOOK_ITEM__


#include "../utils/interfaces/ISerializable.h"

class Item : ISerializable
{
    private:
        const std::string name;
        unsigned durability;
        unsigned price_per_durability;
    public:
        Item(const xml::Tag & t);
        Item(const Item & other) = delete;
        Item & operator=(const Item & other) = delete;
        virtual ~Item() = default;
        
        // bool HasCharges() const;
        // virtual void Use(size_t charges);
        // unsigned Price() const;
        xml::Tag Serialize() const override;
};

#endif
