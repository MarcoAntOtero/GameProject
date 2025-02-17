//
// Created by Marco Otero on 2/3/25.
//
#pragma once
#include "Entity.h"
#include <sstream>
#include <random>
#include <iostream>


constexpr int maxEnemies = 15;
constexpr float enemySpawnTimerMax = 1.5;
const int MAX_TILES = 9;
const int MAX_PLAYER_HEALTH = 100;
const int FRAMES_PER_SECOND = 60;
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
    sf::Texture healthBarTexture;
    sf::Sprite healthBar;
    sf::Texture healthTexture;
    sf::Sprite health;
    int fullHealthWidth;

    std::vector<Enemy*> enemies;
    std::vector<Bullet*> bullets;

    //private functions
    void initVar();
    void initPlayer();
    void initEnemy(sf::Vector2f playerPos);

public:
    Game();
    virtual ~Game();

    void checkCollision();

    bool running() const {return this->window->isOpen();};
    bool getEndGame() const {return this->endGame;}

    //Update functions
    void pollEvents();
    void updateTiles(sf::Vector2f playerPos);
    bool alreadyTile(sf::Vector2f newTilePosition); //needed for update tiles to only create tile if needed
    void updateBullets();
    void updateEnemies();
    void updateView();
    void updateHealthBar();
    void update();

    //Render func, here and entity child classes
    void renderBackground(sf::RenderTarget &target);
    void renderHealthBar(sf::RenderTarget &target);
    void render();
};
