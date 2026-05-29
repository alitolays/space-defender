#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Bonus.h"
#include "Projectile.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

Game::Game()
    : running(true), score(0), frameCounter(0) {
    srand(time(nullptr));

    config.loadConfig("config/medium.txt");

    objects.push_back(std::make_unique<Player>(400, 550));
}

void Game::run() {
    while (running && frameCounter < 200) {
        update();
        draw();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        frameCounter++;
    }

    std::cout << "Game Over!" << std::endl;
    std::cout << "Final score: " << score << std::endl;
}

void Game::update() {
    // Spawns enemies regularly based on configuration
    if (frameCounter % config.getSpawnRate() == 0) {
        spawnEnemy();
    }

    // Random chance to spawn a bonus
    if (rand() % 100 < config.getBonusChance()) {
        spawnBonus();
    }

    // Updates every game object using polymorphism
    for (auto& object : objects) {
        if (object->isActive()) {
            object->update();
        }
    }
}

void Game::draw() {
    std::cout << "------ FRAME " << frameCounter << " ------" << std::endl;
    std::cout << "Score: " << score << std::endl;

    for (auto& object : objects) {
        if (object->isActive()) {
            object->draw();
        }
    }
}

void Game::spawnEnemy() {
    int randomX = rand() % 800;
    int enemySpeed = config.getEnemySpeed();

    objects.push_back(std::make_unique<Enemy>(randomX, 0, enemySpeed));

    std::cout << "Enemy spawned!" << std::endl;
}

void Game::spawnBonus() {
    int randomX = rand() % 800;
    int bonusType = rand() % 3;

    objects.push_back(std::make_unique<Bonus>(randomX, 0, bonusType));
}