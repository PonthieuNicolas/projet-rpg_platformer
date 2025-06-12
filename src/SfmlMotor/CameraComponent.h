#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
#include "Transform.h"

class CameraComponent final : public Component {
public:
    CameraComponent(int width, int height)
        : view(sf::Vector2f(static_cast<float>(width) / 2.f, static_cast<float>(height) / 2.f),
            sf::Vector2f(static_cast<float>(width), static_cast<float>(height))),
        targetTransform(nullptr),
        offset(0.f, 0.f)
    {
        view.setCenter(sf::Vector2f(static_cast<float>(width) / 2.f, static_cast<float>(height) / 2.f));
    }

    virtual ~CameraComponent() override = default;

    inline std::string GetComponentName() const override { return "CameraComponent"; }

    inline void setTarget(Transform* transform) { targetTransform = transform; }
    inline Transform* getTarget() const { return targetTransform; }

    inline sf::View& getView() { return view; }

    inline void setOffset(float x, float y) { offset = { x, y }; }
    inline sf::Vector2f getOffset() const { return offset; }

    void update() {
        if (targetTransform != nullptr) {
            view.setCenter(targetTransform->position + offset);
        }
    }

private:
    sf::View view;
    Transform* targetTransform;
    sf::Vector2f offset;
};
