#include "Player.h"
#include <iostream>

Player::Player(float x, float y)
    : GameObject(x, y, 1.0f), health(100), damage(10) {}

void Player::update() {
    // Player movement would be handled here
}

void Player::draw() {
    std::cout << "Player at position: " << x << ", " << y << std::endl;
}

void Player::onCollision(GameObject* other) {
    health -= 10;

    if (health <= 0) {
        deactivate();
    }
}

int Player::getHealth() const {
    return health;
}