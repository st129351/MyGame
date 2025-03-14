#ifndef AKILLERLOOK_H
#define AKILLERLOOK_H

#include "Amulet.h"

class AKillerLook : public Amulet
{
private:
    const unsigned int fear_percentage;
    const unsigned int slots;
    std::string killer_look_description;
    std::vector<Enemy*> enemies;
    // vector for all enemies, who will be affected by the amulet
public:
    AKillerLook(Enemy& e);
    ~AKillerLook() override;

    void use(Player& p) override;
    void dont_use(Player& p) override;

    unsigned int getFearPercentage() const;
    unsigned int getSlots() const;
    std::string getKillerLookDescription() const;
    void setKillerLookDescription(std::string new_killer_look_description);
};

#endif