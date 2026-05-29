#include "GameObject.h"

GameObject::GameObject(float x, float y, float speed)
    : x(x), y(y), speed(speed), active(true) {}

bool GameObject::isActive() const {
    return active;
}

void GameObject::deactivate() {
    active = false;
}

float GameObject::getX() const {
    return x;
}

float GameObject::getY() const {
    return y;
}