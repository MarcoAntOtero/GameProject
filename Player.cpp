//
// Created by Marco Otero on 2/5/25.
//

#include "Player.h"


Player::Player() {
    this->playerDirection = static_cast<float>(UP);
    this->player.setRotation(this->playerDirection); //equal each other

    this->points = 0;
    this->health = 100;

    this->playerTexture.loadFromFile("/Users/marcootero/CLionProjects/test/Resources/Spaceships/tile007.png");
    this->player.setTexture(playerTexture);
    this->player.setScale(5.f, 5.f);
}

void Player::updatePlayerDirection(sf::RenderWindow &window) {
    //Direction player is facing updates every second and in radian
    this->playerDirection = (M_PI / 180) * this->player.getRotation();  //current angle of player
    /*
     * mousePosView gives global coordinates (x,y) relative to screen not window
     * Vector(aka positon) of mousePosView - Vector(aka position) posPlayer = angle from player to mouse
     * set new angle of player to match mouse
     * Arctan gives theta from y (sin) and x (cos)
     * Convert newAngle from radians to degrees for sfml
     */
    sf::Vector2i mousePosWindow = sf::Mouse::getPosition(window);
    sf::Vector2 mousePosView = window.mapPixelToCoords(mousePosWindow);
    float newAngle = atan2(mousePosView.y - this->player.getPosition().y,
                        mousePosView.x - this->player.getPosition().x);
    float angleInDegrees = ((180.f / M_PI) * newAngle) + 90.f;
    if (angleInDegrees < 0.f) angleInDegrees += 360.f; // Ensure i always positive
    this->player.setRotation(angleInDegrees);

}

void Player::updatePlayer(sf::RenderWindow& window)
{
    updatePlayerDirection(window);
    //Move Player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        this->player.move(0.f, -10.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->player.move(-10.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->player.move(0.f, 10.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->player.move(10.f, 0.f);
    }
    //std::cout << this->playerDirection << std::endl;
}

void Player::renderPlayer(sf::RenderTarget &target)
{
    target.draw(this->player, &this->playerTexture);
}
