#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : public GameObject {
private:
    int health;
    int damage;

public:
    Player(float x, float y);

    void update() override;
    void draw() override;
    void onCollision(GameObject* other) override;

    int getHealth() const;
};

#endif