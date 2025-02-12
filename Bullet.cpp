//
// Created by Marco Otero on 2/10/25.
//

#include "Bullet.h"

Bullet::Bullet(const sf::Texture &texture, float bulletDirection, const sf::Vector2f& bulletPosition,
    float bulletSpeed) {

    this->bulletDamage = 25;
    this->bulletPosition = bulletPosition;
    this->bulletDirection = bulletDirection;
    this->bulletSpeed = bulletSpeed;
    this->bulletLifeTime = 5.f;
    this->bullet.setPosition(bulletPosition);

    this->bullet.setTexture(texture);

    this->bullet.setOrigin(bullet.getLocalBounds().width / 2, bullet.getLocalBounds().height / 2 );//16 x 16 bit png
    this->bullet.setScale(1.f, 1.f);
    this->active = true;
}

void Bullet::update() {
    this->bullet.move(sin(this->bulletDirection) * this->bulletSpeed, cos(this->bulletDirection) * this->bulletSpeed);
    this->bulletLifeTime -= 1.f;
    if(this->bulletLifeTime <= 0) {this->active = false;}
}

void Bullet::render(sf::RenderTarget &target) const {
    target.draw(this->bullet);
}

