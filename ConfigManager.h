#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <string>

class ConfigManager {
private:
    int enemySpeed;
    int spawnRate;
    int playerHealth;
    int bonusChance;

public:
    ConfigManager();

    void loadConfig(const std::string& filename);

    int getEnemySpeed() const;
    int getSpawnRate() const;
    int getPlayerHealth() const;
    int getBonusChance() const;
};

#endif