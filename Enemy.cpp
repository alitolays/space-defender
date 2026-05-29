#include "Enemy.h"
#include <iostream>

Enemy::Enemy(float x, float y, float speed)
    : GameObject(x, y, speed), health(20), damage(10) {}

void Enemy::update() {
    // Enemy moves down every frame
    y += speed;

    if (y > 600) {
        deactivate();
    }
}

void Enemy::draw() {
    std::cout << "Enemy at position: " << x << ", " << y << std::endl;
}

void Enemy::onCollision(GameObject* other) {
    health -= 10;

    if (health <= 0) {
        deactivate();
    }
}