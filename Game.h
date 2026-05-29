#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include "GameObject.h"
#include "ConfigManager.h"

class Game {
private:
    std::vector<std::unique_ptr<GameObject>> objects;
    ConfigManager config;

    bool running;
    int score;
    int frameCounter;

public:
    Game();

    void run();
    void update();
    void draw();
    void spawnEnemy();
    void spawnBonus();
};

#endif