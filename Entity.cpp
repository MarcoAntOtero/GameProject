//
// Created by Marco Otero on 2/10/25.
//

#include "Entity.h"

#include <iostream>

Entity::Entity(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& scale,
               const sf::Vector2f& origin, float speed, float direction, std::vector<Bullet*>& bullets) : bullets(bullets) {
    this->texture = texture;
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(position);
    this->direction = direction;
    this->sprite.setRotation(this->direction);
    this->speed = speed;
    this->sprite.setOrigin(origin.x, origin.y);
    this->sprite.setScale(scale.x, scale.y);
    this->health = 100;
}

void Entity::render(sf::RenderTarget &target) const
{
    target.draw(this->sprite);
}


Player::Player(sf::RenderWindow &window, const sf::Texture &texture, const sf::Vector2f &position,
    const sf::Vector2f &scale, const sf::Vector2f &origin, float speed, float direction, std::vector<Bullet*>& bullets):
    Entity(texture, position, scale, origin, speed, direction, bullets), window(window){
    this->points = 0;
    this->health = 100;
    this->bulletTexture.loadFromFile("/Users/marcootero/CLionProjects/test/Resources/Effects/playerBlast.png");
}

void Player::shoot(std::vector<Bullet*>& bullets) const {
    float angle = this->sprite.getRotation() * (M_PI / 180);
    float offset = sprite.getLocalBounds().height / 2; // Distance from center to tip, so spawns at

    sf::Vector2f bulletDirection(sin(angle), cos(angle));
    const sf::Vector2f bulletPosition = {this->sprite.getPosition() + bulletDirection * offset};

    bullets.push_back(new Bullet(this->bulletTexture,angle,bulletPosition,10.f));
    std::cout << bullets.size() << " bullets created" << std::endl;
}

void Player::updatePlayerDirection() {
    //Direction player is facing updates every second and in radian
    //this->playerDirection = (M_PI / 180) * this->sprite.getRotation();  //current angle of player
    /*
     * mousePosView gives global coordinates (x,y) relative to screen not window
     * Vector(aka position) of mousePosView - Vector(aka position) posPlayer = angle from player to mouse
     * set new angle of player to match mouse
     * Arctan gives theta from y (sin) and x (cos)
     * Convert newAngle from radians to degrees for sfml
     */
    sf::Vector2i mousePosWindow = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosView = window.mapPixelToCoords(mousePosWindow);
    float newAngle = atan2(mousePosView.y - this->sprite.getPosition().y,
                        mousePosView.x - this->sprite.getPosition().x);
    float angleInDegrees = ((180.f / M_PI) * newAngle) + 90.f; //adds 90degree turn because texture faces right in file
    if (angleInDegrees < 0.f) angleInDegrees += 360.f; // Ensure i always positive
    this->sprite.setRotation(angleInDegrees);

}

void Player::update()
{
    updatePlayerDirection();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        shoot(bullets);
    }
    //Move Player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        this->sprite.move(0.f, -10.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->sprite.move(-10.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->sprite.move(0.f, 10.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->sprite.move(10.f, 0.f);
    }
    /*shooting function
    for (const Bullet* bullet : this->bullets) {
        std::cout << "Update bullet at (" << bullet->getPosition().x << ", " << bullet->getPosition().y << ")" << std::endl;
        std::cout << this->bullets.size();
    }*/
}


Enemy::Enemy(const sf::Texture& texture, const sf::Vector2f &position, const sf::Vector2f &scale,
    const sf::Vector2f &origin, float speed, float direction, std::vector<Bullet*>& bullets) :
    Entity(texture, position, scale, origin, speed, direction,bullets){

    this->speed = 5.f;
    this->health = 100;
}

void Enemy::shoot() {
    //nothing
}


void Enemy::updateEnemyDirection() {
    /*
     * Vector(aka position) of player - Vector(aka position) posEnemy = angle from enemy to player
     * Arctan gives theta from y (sin) and x (cos)
     * Convert to degrees from radians
     * Convert newAngle from radians to degrees for sfml
     * Ensure angle  always positive because arctan return negative values
     * Set new angle for enemy rotation
     */
    float newAngle = atan2(playerPos.y - this->sprite.getPosition().y,
                        playerPos.x - this->sprite.getPosition().x);

    this->direction = ((180.f / M_PI) * newAngle);

    if (this->direction < 0.f) this->direction += 360.f;

    this->sprite.setRotation(this->direction);
}

void Enemy::updateEnemyMovement() {
    sf::Vector2f direction = playerPos - this->sprite.getPosition();  //direction vector
    float vecLength = sqrt((direction.x * direction.x) + (direction.y * direction.y)); //find vector length
    if (vecLength != 0) {   //normalize vector so it has length of one
        direction = direction / vecLength;
    }
    this->sprite.move(direction * this->speed);  //move enemy by the normalized vector times speed
}

void Enemy::update()
{
    updateEnemyDirection();
    updateEnemyMovement();
}
