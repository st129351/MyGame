#include "Trader.h"

Trader::Trader(Player& p) : NPC("Trader", "Trader, who can sell you different interesting things.") {}

Trader::~Trader() {}

void Trader::speak()
{
    std::cout << "Hi" << std::endl;
}