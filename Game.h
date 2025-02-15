//
// Created by Marco Otero on 2/3/25.
//
#pragma once
#include "Entity.h"
#include <sstream>
#include <random>

#ifndef GAME_H
#define GAME_H

constexpr float enemySpawnTimerMax = 2.5;
const int MAX_TILES = 9;
class Game
{
private:
    //Variable & Window
    sf::RenderWindow* window{}; //
    sf::Event event{};
    sf::View view;  //needed so window follows player as it moves

    //Background Texture and Tiles, always 3x3 grid
    sf::Texture backGroundTexture;
    sf::Vector2f tileSize;
    std::vector<sf::RectangleShape*> tilesBackGround;
    sf::RectangleShape* original;
    //Text Display
    sf::Text uiText;
    sf::Font font;

    //Game Logic
    bool endGame;
    sf::Clock enemyTimer; // enemy Timer for respawn

    //Game entities and bullets
    Player* player;
    std::vector<Enemy*> enemies;
    std::vector<Bullet*> bullets;

    //private functions
    void initVar();
    void initText();
    void initPlayer();
    void initEnemy(sf::Vector2f playerPos);

public:
    Game();
    virtual ~Game();

    void checkCollision();

    bool running() const {return this->window->isOpen();};
    bool getEndGame() const {return this->endGame;}
    void pollEvents();


    //Update functions
    void updateTiles(sf::Vector2f playerPos);

    bool alreadyTile(sf::Vector2f newTilePosition);

    void updateBullets();
    void updateEnemies();
    void updateText();
    void updateView();
    void update();

    void renderBackground(sf::RenderTarget &target);
    void renderText(sf::RenderTarget& target);
    void render();
};

#endif //GAME_H
