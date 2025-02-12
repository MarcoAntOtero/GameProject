//
// Created by Marco Otero on 2/5/25.
//
/*
#include "Enemy.h"

#include <complex>


Enemy::Enemy(const sf::Vector2f position) {
    this->enemyTexture.loadFromFile("/Users/marcootero/CLionProjects/test/Resources/Spaceships/TinyShip3.png");
    this->enemy.setTexture(enemyTexture);
    this->enemy.setPosition(position);
    this->enemy.setScale(5.f, 5.f);
    this->speed = 5.f;
    this->enemy.setRotation(90.f);
    this->enemy.setOrigin(8,8);
    this->health = 100;
}
void Enemy::updateEnemyDirection(const sf::Vector2f& playerPos) {
    /*
     * Vector(aka positon) of player - Vector(aka position) posEnemy = angle from enemy to player
     * Arctan gives theta from y (sin) and x (cos)
     * Convert to degrees from radians
     * Convert newAngle from radians to degrees for sfml
     * Ensure angle  always positive because arctan return negative values
     * Set new angle for enemy rotation

    float newAngle = atan2(playerPos.y - this->enemy.getPosition().y,
                        playerPos.x - this->enemy.getPosition().x);

    this->enemyDirection = ((180.f / M_PI) * newAngle);

    if (this->enemyDirection < 0.f) this->enemyDirection += 360.f;

    this->enemy.setRotation(this->enemyDirection);
}

void Enemy::updateEnemyMovement(const sf::Vector2f& playerPos) {
    sf::Vector2f direction = playerPos - this->enemy.getPosition();  //direction vector
    float vecLength = sqrt((direction.x * direction.x) + (direction.y * direction.y)); //find vector length
    if (vecLength != 0) {   //normalize vector so it has length of one
        direction = direction / vecLength;
    }
    this->enemy.move(direction * this->speed);  //move enemy by the normalized bector times speed
}

void Enemy::updateEnemy(const sf::Vector2f& playerPos )
{
    updateEnemyDirection(playerPos);
    updateEnemyMovement(playerPos);
}

void Enemy::renderEnemy(sf::RenderTarget& target) const {
    target.draw(this->enemy);
}
*/