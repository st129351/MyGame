#include "GameField.h"

GameField::GameField(Player& p) : player(p)
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if (i==0 || i == 14 || j == 0 || j == 29)
            {
                field[j][i] = '#';
            }
            else
            {
                field[j][i] = ' ';
            }
        }
    }
    playerSpawn(player.getX_pos(), player.getY_pos());
}

GameField::~GameField() {}

void GameField::draw() const
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            std::cout << field[j][i];
        }
        std::cout << std::endl;
    }
}

char GameField::getSymbol(int x, int y) const
{
    if (x >= 0 && x < 30 && y >= 0 && y < 15)
    {
        return field[x][y];
    }
    return ' ';
}

void GameField::setSymbol(int x, int y, char new_symbol)
{
    if (x >= 0 && x < 30 && y >= 0 && y < 15)
    {
        field[x][y] = new_symbol;
    }
}

void GameField::playerSpawn(int x, int y)
{
    char player_symbol = player.getName()[0];
    setSymbol(x, y, player_symbol);
}

void GameField::Movement(char where)
{
    int new_x = player.getX_pos();
    int new_y = player.getY_pos();

    switch (tolower(where))
    {
        case 'w': new_y--; break;
        case 's': new_y++; break;
        case 'a': new_x--; break;
        case 'd': new_x++; break;
    }

    if (getSymbol(new_x, new_y) != '#')
    {
        setSymbol(player.getX_pos(), player.getY_pos(), ' ');
        
        player.setX_pos(new_x);
        player.setY_pos(new_y);

        setSymbol(player.getX_pos(), player.getY_pos(), player.getName()[0]);
    }
}