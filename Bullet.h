//
// Created by Marco Otero on 2/10/25.
//
#pragma once

#include "SFML/Graphics.hpp"
#include <cmath>

class Bullet {
    private:
    sf::Texture bulletTexture;
    sf::Sprite bullet;
    sf::Vector2f scale;
    float bulletDirection;
    sf::Vector2f bulletPosition;
    float bulletSpeed;
    float bulletLifeTime;
    bool active;
    int bulletDamage;
    bool playerBullet;

    public:
    Bullet(const sf::Texture &texture, float bulletDirection, const sf::Vector2f& bulletPosition,
        const sf::Vector2f& scale, int bulletDamage, float bulletSpeed, bool playerBullet);

    bool getPlayerBullet() const{return playerBullet;}
    int getBulletDamage () const {return this->bulletDamage;}
    sf::Vector2f getPosition() const {return this->bullet.getPosition();}
    sf::FloatRect getGlobalBounds() const {return this->bullet.getGlobalBounds();}
    bool isActive() const {return this->active;}

    void update();
    void render(sf::RenderTarget& target) const;
};
