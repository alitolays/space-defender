#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject {
protected:
    float x;
    float y;
    float speed;
    bool active;

public:
    GameObject(float x, float y, float speed);
    virtual ~GameObject() = default;

    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void onCollision(GameObject* other) = 0;

    bool isActive() const;
    void deactivate();

    float getX() const;
    float getY() const;
};

#endif