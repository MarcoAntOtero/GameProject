//
// Created by Marco Otero on 2/3/25.
//
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#ifndef GAME_H
#define GAME_H

class Game
{
private:
    //Variable & Window
    sf::RenderWindow* window{}; //pointer
    sf::Event event{};
    sf::VideoMode videoMode;

    //private functions
    void initVar();
    void initWindow();

public:
    Game();
    virtual ~Game();
    bool getIsRunning() const;
    void pollEvents();
    void update();
    void render();
};

#endif //GAME_H
