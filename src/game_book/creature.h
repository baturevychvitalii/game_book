#ifndef __GAMEBOOK_CREATURE__
#define __GAMEBOOK_CREATURE__


#include "inventory.h"

class Creature : ISerializable
{
    private:
        const std::string name;
        unsigned health;
        unsigned cash;
        Inventory inventory;
    public:
        Creature(const xml::Tag & tag);
        Creature();
        Creature(const Creature & other) = delete;
        Creature & operator=(const Creature & other) = delete;
        ~Creature() = default;

        xml::Tag Serialize() const override;
};

#endif
