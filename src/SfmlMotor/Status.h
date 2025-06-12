#pragma once
#include "Stats.h"
#include <string>

class Status : public Stats {
private:
    std::string value;

public:
    Status(const std::string& value);

    void SetValue(const std::string& v);
    std::string GetValue() const;

    std::string GetComponentName() const override;
};
