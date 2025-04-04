#ifndef APERSEVERANCE_H
#define APERSEVERANCE_H

#include "Amulet.h"

class Player;

class APerseverance : public Amulet
{
private:
    unsigned int additional_health;
    bool was_used;
    std::string perseverance_description;
public:
    APerseverance();
    ~APerseverance() override;

    void use(Player& p) override;
    void warning();

    unsigned int getAdditionalHealth() const;
    void setAdditionalHealth(unsigned int new_additional_health);

    bool getWasUsed() const;
    void setWasUsed(bool new_was_used);
};
#endif