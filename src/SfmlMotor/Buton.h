#pragma once
#include "GUI.h"

class Buton : public GUIComponent {
private:
    std::string label;

public:
    Buton(const std::string& lbl) : label(lbl) {}
    virtual ~Buton() = default;

    void setLabel(const std::string& lbl) { label = lbl; }
    std::string getLabel() const { return label; }

    virtual std::string GetComponentName() const override {
        return "Buton";
    }

    virtual void render() override {
        std::cout << "Buton: " << label << std::endl;
    }
};
