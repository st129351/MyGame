#include "AHeal.h"
#include "Player.h"

AHeal::AHeal() : Amulet(15, false, "bestexp", "increases the experience at every step", 5)
{
    heal_description = "increases the experience at every step";
    heal_value = 5;
}

AHeal::~AHeal() {}

void AHeal::use(Player& p)
{
    unsigned int new_health1 = p.getHealth() + heal_value;
    unsigned int new_health2 = 100;
    if (p.getHealth() < 100)
    {
        if (p.getHealth() > 95)
        {
            p.setHealth(new_health2);
        }
        else
        {
            p.setHealth(new_health1);
        }
    }
    else
    {
        return;
    }
}

void AHeal::dont_use(Player& p)
{
    unsigned int new_health = p.getHealth() - heal_value;
    p.setHealth(new_health);
}

unsigned int AHeal::getHealValue() const
{
    return heal_value;
}

void AHeal::setHealValue(unsigned int new_value)
{
    heal_value = new_value;
}
