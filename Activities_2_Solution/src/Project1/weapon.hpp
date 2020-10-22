#include <string>

enum class WeaponType { MELEE, RANGED, MAGIC, NO_TYPE };

class Weapon
{
public:
    std::string name;
    WeaponType type;
    int range;

    void SetTypeFromString(std::string text)
    {
        if (text == "Melee")
            type = WeaponType::MELEE;
        else if (text == "Ranged")
            type = WeaponType::RANGED;
        else if (text == "Magic")
            type = WeaponType::MAGIC;
        else
            type = WeaponType::NO_TYPE;
    }
};