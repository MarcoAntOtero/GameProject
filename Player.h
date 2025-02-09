//
// Created by Marco Otero on 2/5/25.
//
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <sstream>
#include <cmath>

//in sfml moves clockwise
enum Direction {UP = 270, DOWN = 90, LEFT = 180, RIGHT = 0};

#ifndef PLAYER_H
#define PLAYER_H

class Player {
    private:
    sf::Texture playerTexture;
    sf::Sprite player;
    unsigned points;    //only positive values
    int health;
    float playerDirection;  //radian of sprite

    public:
    Player();

    unsigned getPoints() const {return this-> points;}
    void setPoints(const unsigned points) {this->points = points;}

    int getHealth() const {return this->health;}
    void setHealth(const int health) {this->health = health;}

    void updatePlayerDirection(sf::RenderWindow& window);
    void updatePlayer(sf::RenderWindow& window);
    void renderPlayer(sf::RenderTarget &target);

    sf::FloatRect getGlobalBounds() const {return player.getGlobalBounds(); }
    void setPosition(float xPos, float yPos) {this->player.setPosition(xPos,yPos);}
    sf::Vector2f getPosition() const {return this->player.getPosition();}
    void setOrigin(float xOrigin, float yOrigin) {this->player.setOrigin(xOrigin,yOrigin);}
};


#endif //PLAYER_H
