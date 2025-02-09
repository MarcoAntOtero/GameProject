//
// Created by Marco Otero on 2/5/25.
//
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <ctime>


#ifndef ENEMY_H
#define ENEMY_H

const int maxEnemies = 10;
class Enemy {
private:
    int health;
    //Game Objects
    sf::Texture enemyTexture;
    sf::Sprite enemy;

public:
    Enemy(sf::Vector2f position);
    //Accessors
    sf::Vector2f getPosition() const { return enemy.getPosition(); }
    sf::FloatRect getGlobalBounds() const {return enemy.getGlobalBounds(); }

    void updateEnemy();
    void renderEnemy(sf::RenderTarget& target) const;

};



#endif //ENEMY_H
