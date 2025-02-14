//
// Created by Marco Otero on 2/3/25.
//
#include "Game.h"

#include <iostream>

//Private Functions
void Game::initVar()
{
    //Window Variable
    this->window = nullptr;
    this->window = new sf::RenderWindow({800,600}, "SFML Window");
    this->window->setFramerateLimit(60);
    this->player = nullptr;
    this->backGroundTexture.loadFromFile("Resources/background.jpg");
    this->backGroundTexture.setRepeated(true);
    this->backGround.setScale(4.0,4.0);
    this->backGround.setSize(sf::Vector2f(5000, 5000)); // Larger than texture
    this->backGround.setTexture(&backGroundTexture);
    this->backGround.setTextureRect(sf::IntRect(0, 0, 5000, 5000)); // Makes it repeat

    //View Variable for window to change depending on player movement
    this->view.setSize(this->window->getSize().x * 2.5, this->window->getSize().y * 2.5);

    //Game Logic
    this->endGame = false;
    this->mouseHeld = false;
}

void Game::initText() {
    if (!this->font.loadFromFile("Resources/Arial.ttf")) {
        std::cerr << "Error loading Arial.ttf" << std::endl;
    }
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(30);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}

void Game::initPlayer() {
    //spawns in player
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("Resources/Spaceships/tile007.png"))
        std::cerr << "Error loading Player texture" << std::endl;
    const sf::Vector2f position(this->window->getSize().x / 2, this->window->getSize().y / 2);
    const sf::Vector2f scale(5.f, 5.f);
    const sf::Vector2f origin(8.f,8.f);
    const float speed = 15.0;
    const float direction = 0.f;

    this->player = new Player(*this->window,playerTexture,position,scale, origin, speed, direction, bullets);

}

Game::Game() {
    this->initVar();
    this->initPlayer();
    this->initText();
}

Game::~Game() {
    delete this->window;
    for (const auto &enemy : enemies) {
        delete enemy;
    }
    for (const auto &bullet : bullets) {
        delete bullet;
    }
    delete this->player;
    enemies.clear();
}


/*
 *
 *Game and Update Functions
 *
 *
 *
 *
 *
 *
 */

void Game::pollEvents()
{
    while (this->window->pollEvent(this->event))
    {
        if (this->event.type == sf::Event::Closed)
            this->window->close();
        else if (this->event.type == sf::Event::KeyPressed) {
            if (this->event.key.code == sf::Keyboard::Escape) {this->window->close();}
        }
    }
}

void Game::checkCollision() {
    for (size_t i = 0; i < this->bullets.size(); i++) {
        if (bullets[i]->getGlobalBounds().intersects(this->player->getGlobalBounds()) && !bullets[i]->getPlayerBullet())
        {
            this->player->setHealth(this->player->getHealth() - bullets[i]->getBulletDamage());
            delete bullets[i];
            bullets.erase(bullets.begin() + i);

        }
        for (size_t j = 0; j < enemies.size(); j++) {
            if (bullets[i]->getGlobalBounds().intersects(enemies[j]->getGlobalBounds()) && bullets[i]->getPlayerBullet())
            {
                this->enemies[j]->setHealth(this->enemies[j]->getHealth() - bullets[i]->getBulletDamage());
                delete bullets[i];      //delete bullet when intersects and lower enemy health
                bullets.erase(bullets.begin() + i);
            }
        }
    }
}

void Game::updateBullets() {
    for (size_t i = 0; i < this->bullets.size(); i++) {
        bullets[i]->update();
        if (!bullets[i]->isActive()) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        }
    }
    checkCollision();
}



void Game::initEnemy(sf::Vector2f playerPos) {
    //needs playerpos so the enemy can follow it
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(playerPos.x - (this->window->getSize().x / 2.f),
                                            playerPos.x + (this->window->getSize().x / 2.f));

    std::uniform_int_distribution<int> disty(playerPos.y - (this->window->getSize().y / 2.f),
                                            playerPos.y + (this->window->getSize().y / 2.f));
    const float x = static_cast<float>(dist(gen));
    const float y = static_cast<float>(disty(gen));

    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("Resources/Spaceships/TinyShip3.png");
    const sf::Vector2f position(x,y);
    const sf::Vector2f scale(5.f, 5.f);
    const sf::Vector2f origin(8.f,8.f);
    const float speed = 10.0;
    const float direction = 0.0;
    this->enemies.push_back(new Enemy(enemyTexture,position, scale, origin, speed, direction,bullets));
}



void Game::updateEnemies() {
    // Ensure the number of enemies is always `maxEnemies`
    while (this->enemies.size() < maxEnemies && this->enemyTimer.getElapsedTime().asSeconds() >= enemySpawnTimerMax) {
        initEnemy(this->player->getPosition()); //adds enemy to vector
        this->enemyTimer.restart();
    }

    // Update enemies, where they move and
    for (size_t i = 0; i < enemies.size(); i++) {

        enemies[i]->setPlayerPos(this->player->getPosition());
        enemies[i]->update();
        if (this->enemies[i]->getHealth() <= 0) {
            // Delete enemy
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
            this->player->setPoints(this->player->getPoints() + 10);
            this->player->setHealth(this->player->getHealth() + 10);
        }
    }

}


void Game::updateText() {
    std::stringstream ss;
    ss << "Points: " << this->player->getPoints() << std::endl;
    ss << "Health: " << this->player->getHealth() << std::endl;
    this->uiText.setString(ss.str());
}

void Game::updateView() {
    this->view.setCenter(player->getPosition());
    this->window->setView(view);
}

void Game::update()
{
    //all update functions
    this->pollEvents();
    if (!this->endGame) {
        this->updateText();
        this->updateView();
        this->player->update(); // Update player first
        this->updateEnemies();  // Update enemies
        this->updateBullets();
    }
    //End game condition after enemies
    if (this->player->getHealth() <= 0) {
        this->endGame = true;
    }
}



/*
 *
 *RENDER FUNCTIONS
 *
 *
 */


void Game::renderBackground(sf::RenderTarget &target) {
    target.draw(this->backGround);
}


void Game::renderText(sf::RenderTarget &target) {
    target.draw(this->uiText);
}

void Game::render() {

    //clear frame
    this->window->clear();
    this->renderBackground(*this->window);
    this->player->render(*this->window);
    this->renderText(*this->window);

    for (size_t i = 0; i < this->bullets.size(); i++)
    {
        this->bullets[i]->render(*window);
    }
    for (const auto& enemy : this->enemies) {
        enemy->render(*window);
    }
    this->window->display();
}
