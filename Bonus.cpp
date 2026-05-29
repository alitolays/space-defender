#include "Bonus.h"
#include <iostream>

Bonus::Bonus(float x, float y, int bonusType)
    : GameObject(x, y, 1.0f), bonusType(bonusType) {}

void Bonus::update() {
    y += speed;

    if (y > 600) {
        deactivate();
    }
}

void Bonus::draw() {
    std::cout << "Bonus type " << bonusType << " at position: " << x << ", " << y << std::endl;
}

void Bonus::onCollision(GameObject* other) {
    deactivate();
}