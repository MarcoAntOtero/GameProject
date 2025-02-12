//
// Created by Marco Otero on 2/10/25.
//

#ifndef BULLET_H
#define BULLET_H
#include "SFML/Graphics.hpp"


class Bullet {
    private:
    sf::Texture bulletTexture;
    sf::Sprite bullet;
    sf::Vector2f bulletPosition;
    sf::Vector2f bulletSpeed;

    public:
    Bullet();

};



#endif //BULLET_H
