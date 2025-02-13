//
// Created by Marco Otero on 2/10/25.
//

#include "Bullet.h"

Bullet::Bullet(const sf::Texture &texture, const float bulletDirection, const sf::Vector2f& bulletPosition,
    const float bulletSpeed) {

    this->bulletDamage = 10;
    this->bulletPosition = bulletPosition;
    this->bulletDirection = bulletDirection;
    this->bulletSpeed = bulletSpeed;
    this->bulletLifeTime = 175.f;
    this->bullet.setPosition(bulletPosition);

    this->bullet.setTexture(texture);

    this->bullet.setOrigin(bullet.getLocalBounds().width / 2, bullet.getLocalBounds().height / 2 );//16 x 16 bit png
    this->bullet.setScale(2.0, 2.0);
    this->active = true;

    this->bullet.setRotation(this->bulletDirection * (180 / M_PI)); //have to convert back to degrees
}

void Bullet::update() {
    //bullet direction is angle and move it by the cos(x direction) and sin(y direction)
    this->bullet.move(cos(this->bulletDirection) * this->bulletSpeed, sin(this->bulletDirection) * this->bulletSpeed);
    this->bulletLifeTime -= 1.f;
    if(this->bulletLifeTime < 0) {this->active = false;}
}

void Bullet::render(sf::RenderTarget &target) const {
    target.draw(this->bullet);
}

