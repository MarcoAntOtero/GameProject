//
// Created by Marco Otero on 2/5/25.
//

#include "Enemy.h"

Enemy::Enemy(const sf::Vector2f position) {
    this->enemyTexture.loadFromFile("/Users/marcootero/CLionProjects/test/Resources/Spaceships/TinyShip3.png");
    this->enemy.setTexture(enemyTexture);
    this->enemy.setPosition(position);
    this->enemy.setScale(5.f, 5.f);
    this->health = 100;
}

void Enemy::updateEnemy()
{
    this->enemy.move(0,2.f);
}

void Enemy::renderEnemy(sf::RenderTarget& target) const {
    target.draw(this->enemy);
}
