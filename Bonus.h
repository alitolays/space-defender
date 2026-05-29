#ifndef BONUS_H
#define BONUS_H

#include "GameObject.h"

class Bonus : public GameObject {
private:
    int bonusType;

public:
    Bonus(float x, float y, int bonusType);

    void update() override;
    void draw() override;
    void onCollision(GameObject* other) override;
};

#endif