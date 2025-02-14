//
// Created by Marco Otero on 2/3/25.
//
#pragma once
#include "Entity.h"
#include <sstream>
#include <random>

#ifndef GAME_H
#define GAME_H

constexpr float enemySpawnTimerMax = 2.5;

class Game
{
private:
    //Variable & Window
    sf::RenderWindow* window{}; //
    sf::Event event{};
    sf::View view;  //needed so window follows player as it moves
    sf::Texture backGroundTexture;
    sf::RectangleShape backGround;

    //Text Display
    sf::Text uiText;
    sf::Font font;

    //Game Logic
    bool endGame;
    bool mouseHeld;
    sf::Clock enemyTimer; // enemy Timer for respawn

    //Game entities and bullets
    Player* player;
    std::vector<Enemy*> enemies;
    std::vector<Bullet*> bullets;

    //private functions
    void initVar();
    void initText();
    void initPlayer();
    void initEnemy(sf::Vector2f playerPos);

public:
    Game();
    virtual ~Game();


    void checkCollision();

    bool running() const {return this->window->isOpen();};
    bool getEndGame() const {return this->endGame;}
    void pollEvents();


    //Update functions
    void updateBullets();
    void updateEnemies();
    void updateText();
    void updateView();
    void update();

    void renderBackground(sf::RenderTarget &target);
    void renderText(sf::RenderTarget& target);
    void render();
};

#endif //GAME_H
