#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "Enemy.h"
#include "Player.h"
#include "Amulet.h"

class GameField
{
private:
    char field[30][15];
    Player player;
    // Mucus mucus;
public:
    GameField(Player& p);
    ~GameField();

    void draw() const;
    // for drawing the field in the console 
    // not change the field --> const

    char getSymbol(int x, int y) const;
    void setSymbol(int x, int y, char symbol);

    void playerSpawn(int x, int y);
    // void enemySpawn(int x, int y);

    void Movement(char where);
    // for movement of the player
};


#endif