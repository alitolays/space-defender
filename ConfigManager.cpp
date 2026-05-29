#include "ConfigManager.h"
#include <fstream>
#include <iostream>

ConfigManager::ConfigManager()
    : enemySpeed(2), spawnRate(60), playerHealth(100), bonusChance(20) {}

void ConfigManager::loadConfig(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Could not open config file. Default settings used." << std::endl;
        return;
    }

    std::string key;
    char equals;
    int value;

    while (file >> key >> equals >> value) {
        if (key == "enemySpeed") {
            enemySpeed = value;
        } else if (key == "spawnRate") {
            spawnRate = value;
        } else if (key == "playerHealth") {
            playerHealth = value;
        } else if (key == "bonusChance") {
            bonusChance = value;
        }
    }

    file.close();
}

int ConfigManager::getEnemySpeed() const {
    return enemySpeed;
}

int ConfigManager::getSpawnRate() const {
    return spawnRate;
}

int ConfigManager::getPlayerHealth() const {
    return playerHealth;
}

int ConfigManager::getBonusChance() const {
    return bonusChance;
}