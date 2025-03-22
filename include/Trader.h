#ifndef TRADER_H
#define TRADER_H

#include "NPC.h"
#include "Player.h"

class Player;
// forward declaration

class Trader : public NPC
{
public:
    Trader(Player& p);
    ~Trader() override;

    void speak() override;
};

#endif