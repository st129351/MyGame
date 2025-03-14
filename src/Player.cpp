#include "Player.h"

Player::Player(): Fighter(""), max_level(3), inventory(*this)
{
    this->level = 1;
    this->exp = 0;
    this->gold = 0;
    this->x_pos = 14;  // начальная позиция x
    this->y_pos = 7;   // начальная позиция y (центр по вертикали)
    std::cout << "Enter the name of your hero: ";
    std::cin >> name;
    setName(name);
}

void Player::onDeath()
{
    std::cout << "GAME OVER" << std::endl;
    std::cout << "YOU ARE LOSE 💀" << std::endl;
}

void Player::levelUp()
{
    if (level < max_level)
    {
        setLevel(getLevel() + 1);
        setExp(0);
        setGold(getGold() + level * 10);

        unsigned int new_damage = getDamage() + 10;
        setDamage(new_damage);

        unsigned int new_health = getHealth() + 15;
        setHealth(new_health);

        std::cout << "You are level up! 🔥" << std::endl;
    }
}

std::string Player::showInventory()
{
    std::cout << "INVENTORY" << std::endl;
    return inventory.show();
}

// getters 
unsigned int Player::getExp() const
{
    return exp;
}

unsigned int Player::getGold() const
{
    return gold;
}

unsigned int Player::getLevel() const
{
    return level;
}

unsigned int Player::getMaxLevel() const
{
    return max_level;
}

std::string Player::getName() const
{
    return name;
}

// setters
void Player::setExp(unsigned int new_exp)
{
    exp = new_exp;
}

void Player::setGold(unsigned int new_gold)
{
    gold = new_gold;
}

void Player::setLevel(unsigned int new_level)
{
    level = new_level;
}

void Player::setName(const std::string& new_name)
{
    name = new_name;
}

unsigned int Player::getX_pos() const
{
    return x_pos;
}

unsigned int Player::getY_pos() const
{
    return y_pos;
}

void Player::setX_pos(unsigned int new_x_pos)
{
    x_pos = new_x_pos;
}

void Player::setY_pos(unsigned int new_y_pos)
{
    y_pos = new_y_pos;
}
