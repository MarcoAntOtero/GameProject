//
// Created by Marco Otero on 2/5/25.
//

#include "Player.h"


Player::Player() {
    this->points = 0;
    this->health = 100;
    this->playerTexture.loadFromFile("/Users/marcootero/CLionProjects/test/Resources/Spaceships/tile007.png");
    this->player.setTexture(playerTexture);
    this->player.setOrigin(this->playerTexture.getSize().x / 2, this->playerTexture.getSize().y / 2);
    this->player.setScale(5.f, 5.f);
}

void Player::updatePlayer()
{
    this->player.move(1.f, 0.f);
}

void Player::renderPlayer(sf::RenderTarget &target)
{
    target.draw(this->player, &this->playerTexture);
}
