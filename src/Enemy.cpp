#include "Enemy.h"

Enemy::Enemy(std::string name) : Fighter(name) {}

std::string Enemy::getEnemyDescription() const
{
    return enemy_description;
}

void Enemy::setEnemyDescription(const std::string& new_enemy_description)
{
    enemy_description = new_enemy_description;
}

unsigned int Enemy::getIQ() const
{
    return iq;
}

void Enemy::setIQ(unsigned int new_iq)
{
    iq = new_iq;
}

