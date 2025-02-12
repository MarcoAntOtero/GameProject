#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"

const int maxEnemies = 10;
// In SFML, moves clockwise
enum Direction { UP = 270, DOWN = 90, LEFT = 180, RIGHT = 0 };

class Entity {
protected:
    sf::Texture texture;
    sf::Sprite sprite;
    float speed;
    float direction;

public:
    Entity(const sf::Texture& texture, const sf::Vector2f& position,
           const sf::Vector2f& scale, const sf::Vector2f& origin, float speed, float direction);

    virtual ~Entity() = default;

    virtual void update() = 0;  // Pure virtual function (abstract)
    void render(sf::RenderTarget& target) const;

    sf::Vector2f getPosition() const { return sprite.getPosition(); }
    sf::FloatRect getGlobalBounds() const { return sprite.getGlobalBounds(); }

    void setPosition(float x, float y) { sprite.setPosition(x, y); }
    void setOrigin(float x, float y) { sprite.setOrigin(x, y); }
};

class Player : public Entity {
private:
    unsigned points;    // Only positive values
    int health;
    sf::RenderWindow& window;

public:
    // Accessors
    unsigned getPoints() const { return points; }
    void setPoints(unsigned points) { this->points = points; }

    int getHealth() const { return health; }
    void setHealth(int health) { this->health = health; }

    Player(sf::RenderWindow& window, const sf::Texture& texture, const sf::Vector2f& position,
           const sf::Vector2f& scale, const sf::Vector2f& origin, float speed, float direction);

    void shooting();
    void update() override;
    void updatePlayerDirection();
};

class Enemy : public Entity {
private:
    int health;
    sf::Vector2f playerPos;

public:
    Enemy(const sf::Texture& texture, const sf::Vector2f& position,
          const sf::Vector2f& scale, const sf::Vector2f& origin, float speed, float direction);

    void update() override;
    void setPlayerPos(const sf::Vector2f& playerPos) { this->playerPos = playerPos; }
    sf::Vector2f getPlayerPos() const { return playerPos; }

    void updateEnemyDirection();
    void updateEnemyMovement();
};