//
// Created by Marco Otero on 2/3/25.
//
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <ctime>

#ifndef GAME_H
#define GAME_H

class Game
{
private:
    //Variable & Window
    sf::RenderWindow* window{}; //pointer
    sf::Event event{};
    sf::VideoMode videoMode;

    //Mouse positions
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Game Logic
    unsigned points;    //only positive values
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;


    //Game Objects
    sf::RectangleShape enemy;
    std::vector<sf::RectangleShape> enemies;

    //private functions
    void initVar();
    void initWindow();
    void initEnemies();

public:
    Game();
    virtual ~Game();
    bool getIsRunning() const;

    void spawnEnemy();
    void pollEvents();

    void updateMousePos();
    void update();
    void updateEnemies();

    void renderEnemies();
    void render();
};

#endif //GAME_H
