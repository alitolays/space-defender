#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GameObject.h"

class Projectile : public GameObject {
private:
    int damage;

public:
    Projectile(float x, float y);

    void update() override;
    void draw() override;
    void onCollision(GameObject* other) override;
};

#endif