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

void Enemy::updateEnemyDirection(const sf::Vector2f& playerPos) {
    //Direction player is facing updates every second and in radian
    this->enemyDirection = (M_PI / 180) * this->enemy.getRotation();  //current angle of enemy
    /*
     * mousePosView gives global coordinates (x,y) relative to screen not window
     * Vector(aka positon) of mousePosView - Vector(aka position) posPlayer = angle from player to mouse
     * set new angle of player to match mouse
     * Arctan gives theta from y (sin) and x (cos)
     * Convert newAngle from radians to degrees for sfml
     */
    float newAngle = atan2(playerPos.y - this->enemy.getPosition().y,
                        playerPos.x - this->enemy.getPosition().x);
    float angleInDegrees = ((180.f / M_PI) * newAngle);
    if (angleInDegrees < 0.f) angleInDegrees += 360.f; // Ensure agle  always positive
    this->enemy.setRotation(angleInDegrees);

}

void Enemy::updateEnemy(const sf::Vector2f& playerPos )
{
    updateEnemyDirection(playerPos);
    this->enemy.move(0,2.f);
}

void Enemy::renderEnemy(sf::RenderTarget& target) const {
    target.draw(this->enemy);
}
