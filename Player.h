//
// Created by Marco Otero on 2/5/25.
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

#ifndef PLAYER_H
#define PLAYER_H

class Player {
    private:
    sf::Texture playerTexture;
    sf::Sprite player;
    unsigned points;    //only positive values
    int health;

    public:
    Player();

    unsigned getPoints() const {return this-> points;}
    void setPoints(const unsigned points) {this->points = points;}

    int getHealth() const {return this->health;}
    void setHealth(const int health) {this->health = health;}

    void updatePlayer();
    void renderPlayer(sf::RenderTarget &target);
};


#endif //PLAYER_H
