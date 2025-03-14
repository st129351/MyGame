#ifndef ENEMY_H
#define ENEMY_H

#include "Fighter.h"

class Enemy : public Fighter
{
private: 
    std::string enemy_description;
    unsigned int iq;
public:
    Enemy(std::string name);
    virtual ~Enemy() = default;

    std::string getEnemyDescription() const;
    void setEnemyDescription(const std::string& new_enemy_description);

    unsigned int getIQ() const;
    void setIQ(unsigned int new_iq);
};

#endif