#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"

class Enemy : public GameObject {
private:
    int health;
    int damage;

public:
    Enemy(float x, float y, float speed);

    void update() override;
    void draw() override;
    void onCollision(GameObject* other) override;
};

#endif