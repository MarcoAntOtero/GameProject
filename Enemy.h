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
    float enemyDirection;
    float speed;
    //Game Objects
    sf::Texture enemyTexture;
    sf::Sprite enemy;

public:

    Enemy(sf::Vector2f position);

    void updateEnemyDirection(const sf::Vector2f& playerPos);
    void updateEnemyMovement(const sf::Vector2f& playerPos);

    //Accessors
    sf::Vector2f getPosition() const { return enemy.getPosition(); }
    sf::FloatRect getGlobalBounds() const {return enemy.getGlobalBounds(); }

    void updateEnemy(const sf::Vector2f& playerPos);
    void renderEnemy(sf::RenderTarget& target) const;

};



#endif //ENEMY_H
