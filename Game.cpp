#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

Game::Game()
    : window(sf::VideoMode({800, 600}), "Choose difficulty: 1 Easy | 2 Medium | 3 Hard"),
      scoreText(font, "", 28),
      score(0),
      health(3),
      maxHealth(3),
      enemySpeed(120.f),
      enemySpawnDelay(1.2f),
      enemySpawnTimer(0.f),
      difficultySelected(false)
{
    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
{
    window.close();
}

    scoreText.setFont(font);
    scoreText.setString("SCORE: 0");
    scoreText.setFillColor(sf::Color::White);
    scoreText.setStyle(sf::Text::Bold);
    scoreText.setPosition({620.f, 20.f});

    srand(static_cast<unsigned>(time(nullptr)));
    createPlayer();
}

void Game::createPlayer()
{
    player.setPointCount(4);

    player.setPoint(0, {25.f, 0.f});
    player.setPoint(1, {50.f, 45.f});
    player.setPoint(2, {25.f, 35.f});
    player.setPoint(3, {0.f, 45.f});

    player.setFillColor(sf::Color::Green);
    player.setPosition({375.f, 520.f});
}

void Game::run()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        processEvents();

        if (difficultySelected)
            update(deltaTime);

        render();
    }
}

void Game::processEvents()
{
    while (const auto event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
    }

    if (!difficultySelected)
        selectDifficulty();
}

void Game::selectDifficulty()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
    {
        enemySpeed = 90.f;
        enemySpawnDelay = 1.5f;
        health = 5;
        maxHealth = 5;
        difficultySelected = true;
        updateTitle();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
    {
        enemySpeed = 130.f;
        enemySpawnDelay = 1.0f;
        health = 4;
        maxHealth = 4;
        difficultySelected = true;
        updateTitle();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
    {
        enemySpeed = 180.f;
        enemySpawnDelay = 0.6f;
        health = 3;
        maxHealth = 3;
        difficultySelected = true;
        updateTitle();
    }
}

void Game::update(float deltaTime)
{
    float playerSpeed = 300.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        player.move({-playerSpeed * deltaTime, 0.f});

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        player.move({playerSpeed * deltaTime, 0.f});

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        player.move({0.f, -playerSpeed * deltaTime});

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        player.move({0.f, playerSpeed * deltaTime});

    static bool canShoot = true;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        if (canShoot)
        {
            shoot();
            canShoot = false;
        }
    }
    else
    {
        canShoot = true;
    }

    enemySpawnTimer += deltaTime;

    if (enemySpawnTimer >= enemySpawnDelay)
    {
        enemySpawnTimer = 0.f;
        spawnEnemy();
    }

    for (auto& enemy : enemies)
        enemy.move({0.f, enemySpeed * deltaTime});

    for (auto& bullet : bullets)
        bullet.move({0.f, -500.f * deltaTime});

    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const sf::ConvexShape& enemy)
            {
                return enemy.getPosition().y > 650.f;
            }),
        enemies.end()
    );

    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
            [](const sf::RectangleShape& bullet)
            {
                return bullet.getPosition().y < -20.f;
            }),
        bullets.end()
    );

    for (size_t i = 0; i < bullets.size(); i++)
    {
        for (size_t j = 0; j < enemies.size(); j++)
        {
            if (bullets[i].getGlobalBounds().findIntersection(enemies[j].getGlobalBounds()))
            {
                bullets.erase(bullets.begin() + i);
                enemies.erase(enemies.begin() + j);

                score += 10;
                updateTitle();

                return;
            }
        }
    }

    for (size_t i = 0; i < enemies.size(); i++)
    {
        if (player.getGlobalBounds().findIntersection(enemies[i].getGlobalBounds()))
        {
            enemies.erase(enemies.begin() + i);
            health--;

            updateTitle();

            if (health <= 0)
                window.setTitle("GAME OVER | Final score: " + std::to_string(score));

            break;
        }
    }
}

void Game::shoot()
{
    sf::RectangleShape bullet({6.f, 20.f});
    bullet.setFillColor(sf::Color::Yellow);

    bullet.setPosition({
        player.getPosition().x + 22.f,
        player.getPosition().y - 10.f
    });

    bullets.push_back(bullet);
}

void Game::spawnEnemy()
{
    sf::ConvexShape enemy;
    enemy.setPointCount(6);

    enemy.setPoint(0, {0.f, 10.f});
    enemy.setPoint(1, {15.f, 0.f});
    enemy.setPoint(2, {35.f, 0.f});
    enemy.setPoint(3, {50.f, 10.f});
    enemy.setPoint(4, {40.f, 35.f});
    enemy.setPoint(5, {10.f, 35.f});

    enemy.setFillColor(sf::Color::Red);

    float x = static_cast<float>(rand() % 740);
    enemy.setPosition({x, -40.f});

    enemies.push_back(enemy);
}

void Game::drawHearts()
{
    for (int i = 0; i < health; i++)
    {
        sf::ConvexShape heart;
        heart.setPointCount(10);

        heart.setPoint(0, {16.f, 28.f});
        heart.setPoint(1, {0.f, 12.f});
        heart.setPoint(2, {0.f, 4.f});
        heart.setPoint(3, {8.f, 0.f});
        heart.setPoint(4, {16.f, 6.f});
        heart.setPoint(5, {24.f, 0.f});
        heart.setPoint(6, {32.f, 4.f});
        heart.setPoint(7, {32.f, 12.f});
        heart.setPoint(8, {16.f, 28.f});
        heart.setPoint(9, {16.f, 28.f});

        heart.setFillColor(sf::Color::Red);
        heart.setPosition({20.f + i * 42.f, 20.f});

        window.draw(heart);
    }
}

void Game::updateTitle()
{
    scoreText.setString("SCORE: " + std::to_string(score));
}

void Game::render()
{
    window.clear(sf::Color::Black);

    if (difficultySelected)
    {
        window.draw(player);

        for (auto& enemy : enemies)
            window.draw(enemy);

        for (auto& bullet : bullets)
            window.draw(bullet);

        drawHearts();
        window.draw(scoreText);
        updateTitle();
    }



    window.display();
}