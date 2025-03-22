#ifndef BESTEXP_H
#define BESTEXP_H

#include "Amulet.h"

class BestExp : public Amulet
{
private:
    unsigned int add_exp;
    std::string best_exp_description; // help variable
    const unsigned int slots;
public:
    BestExp(Player& p);
    ~BestExp() override;

    unsigned int getAddExp() const;
    void setAddExp(unsigned int new_exp);
    std::string getBestExpDescription() const;
    void setBestExpDescription();

    unsigned int getSlots() const;

    void use(Player& p) override;
    void dont_use(Player& p) override;
};

#endif