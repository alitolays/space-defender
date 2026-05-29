#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Game
{
private:
    sf::RenderWindow window;

    sf::ConvexShape player;
    std::vector<sf::ConvexShape> enemies;
    std::vector<sf::RectangleShape> bullets;

    int score;
    int health;
    int maxHealth;

    float enemySpeed;
    float enemySpawnDelay;
    float enemySpawnTimer;

    bool difficultySelected;

    void processEvents();
    void update(float deltaTime);
    void render();

    void selectDifficulty();
    void createPlayer();
    void spawnEnemy();
    void shoot();
    void updateTitle();
    void drawHearts();
    sf::Font font;
    sf::Text scoreText;

public:
    Game();
    void run();
};

#endif