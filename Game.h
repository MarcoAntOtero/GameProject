//
// Created by Marco Otero on 2/3/25.
//
#pragma once
#include "Entity.h"
#include <sstream>
#include <random>

#ifndef GAME_H
#define GAME_H

const float enemySpawnTimerMax = 10.f;

class Game
{
private:
    //Variable & Window
    sf::RenderWindow* window{}; //pointer
    sf::Event event{};
    sf::VideoMode videoMode;
    sf::View view;

    //Mouse positions
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Text Display
    sf::Text uiText;
    sf::Font font;

    //Game Logic
    bool endGame;
    bool mouseHeld;
    sf::Clock clock; // enemy Timer

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

    void updateBullets();
    void checkCollision();

    bool running() const {return this->window->isOpen();};
    bool getEndGame() const {return this->endGame;}
    void pollEvents();


    void updateMousePos();
    void updateEnemies();
    void updateText();
    void updateView();

    void update();

    void renderText(sf::RenderTarget& target);
    void render();
};

#endif //GAME_H
