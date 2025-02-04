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
#include <sstream>


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

    //Text Display
    sf::Text uiText;
    sf::Font font;

    //Game Logic
    bool endGame;
    unsigned points;    //only positive values
    int health;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    bool mouseHeld;

    //Game Objects
    sf::RectangleShape enemy;
    std::vector<sf::RectangleShape> enemies;
    //sf::Texture playerTexture();
    //private functions
    void initVar();
    void initWindow();
    void initText();
    //void initEnemies();

public:
    Game();
    virtual ~Game();

    bool running() const {return this->window->isOpen();};
    bool getEndGame() const {return this->endGame;}

    void spawnEnemy();
    void pollEvents();

    void updateMousePos();
    void updateText();
    void update();
    void updateEnemies();

    void renderText(sf::RenderTarget& target); //not rendering to window
    void renderEnemies(sf::RenderTarget& target);
    void render();
};

#endif //GAME_H
