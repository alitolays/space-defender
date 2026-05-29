#include "Projectile.h"
#include <iostream>

Projectile::Projectile(float x, float y)
    : GameObject(x, y, 5.0f), damage(10) {}

void Projectile::update() {
    y -= speed;

    if (y < 0) {
        deactivate();
    }
}

void Projectile::draw() {
    std::cout << "Projectile at position: " << x << ", " << y << std::endl;
}

void Projectile::onCollision(GameObject* other) {
    deactivate();
}