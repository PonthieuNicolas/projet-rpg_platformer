#pragma once
#include "Stats.h"

class Experience : public Stats {
private:
    int value;

public:
    Experience(int value);

    void SetValue(int v);
    int GetValue() const;

    std::string GetComponentName() const override;
};
