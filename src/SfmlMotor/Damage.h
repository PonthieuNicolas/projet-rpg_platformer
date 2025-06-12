#pragma once
#include "Stats.h"

class Damage : public Stats {
private:
    int value;

public:
    Damage(int value);

    void SetValue(int v);
    int GetValue() const;

    std::string GetComponentName() const override;
};
