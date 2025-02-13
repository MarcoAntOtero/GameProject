//
// Created by Marco Otero on 2/10/25.
//

#ifndef BULLET_H
#define BULLET_H
#include "SFML/Graphics.hpp"
#include <cmath>

class Bullet {
    private:
    sf::Texture bulletTexture;
    sf::Sprite bullet;
    float bulletDirection;
    sf::Vector2f bulletPosition;
    float bulletSpeed;
    float bulletLifeTime;
    bool active;
    int bulletDamage;

    public:
    Bullet(const sf::Texture &texture, float bulletDirection, const sf::Vector2f& bulletPosition,
    float bulletSpeed);
    int getBulletDamage () const {return this->bulletDamage;};
    sf::Vector2f getPosition() const {return this->bullet.getPosition();}

    sf::FloatRect getGlobalBounds() const {return this->bullet.getGlobalBounds();}
    bool isActive() const {return this->active;};
    void update();
    void render(sf::RenderTarget& target) const;
};



#endif //BULLET_H
