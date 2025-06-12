#pragma once
#include "Stats.h"

class Life : public Stats {
private:
    int value;

public:
    Life(int value);

    void SetValue(int v);
    int GetValue() const;
    void takeDamage(int damage) override;

    std::string GetComponentName() const override;
    
    void heal(int amount);
};
