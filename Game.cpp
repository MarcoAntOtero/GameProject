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
    this->window = new sf::RenderWindow({2560,1664}, "SFML Window");
    this->window->setFramerateLimit(60);
    this->player = nullptr;
    //this->window->setMouseCursorVisible(false);

    //View Variable
    view.setCenter(this->window->getSize().x / 2, this->window->getSize().y / 2);
    view.setSize({2560.f, 1664.f});

    //Game Logic
    this->endGame = false;
    this->mouseHeld = false;
}

void Game::initText() {
    if (!this->font.loadFromFile("/Users/marcootero/CLionProjects/test/Resources/Arial.ttf")) {
        std::cerr << "Error loading Arial.ttf" << std::endl;
    }
    else{std::cout << "successful load of texture" << std::endl;}
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(30);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}

void Game::initPlayer() {
    //spawns in player
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("/Users/marcootero/CLionProjects/test/Resources/Spaceships/tile007.png"))
        std::cerr << "Error loading Playertext" << std::endl;
    const sf::Vector2f position(this->window->getSize().x / 2, this->window->getSize().y / 2);
    const sf::Vector2f scale(5.f, 5.f);
    const sf::Vector2f origin(8.f,8.f);
    const float speed = 5.f;
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
        /*if (bullets[i]->getGlobalBounds().intersects(this->player->getGlobalBounds()))
        {
            //delete bullets[i];
            bullets.erase(bullets.begin() + i);
            this->player->setHealth(this->player->getHealth() - bullets[i]->getBulletDamage());

        }*/
        for (const auto& enemy : enemies) {
            if (bullets[i]->getGlobalBounds().intersects(enemy->getGlobalBounds()))
            {
                delete bullets[i];
                bullets.erase(bullets.begin() + i);
                enemy->setHealth(this->player->getHealth() - 10);
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

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(playerPos.x - (this->window->getSize().x / 2.f),
                                            playerPos.x + (this->window->getSize().x / 2.f));

    std::uniform_int_distribution<int> disty(playerPos.y - (this->window->getSize().y / 2.f),
                                            playerPos.y + (this->window->getSize().y / 2.f));
    const float x = static_cast<float>(dist(gen));
    const float y = static_cast<float>(disty(gen));

    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("/Users/marcootero/CLionProjects/test/Resources/Spaceships/TinyShip3.png");
    const sf::Vector2f position(x,y);
    const sf::Vector2f scale(5.f, 5.f);
    const sf::Vector2f origin(8.f,8.f);
    const float speed = 10.f;
    const float direction = 90.f;
    this->enemies.push_back(new Enemy(enemyTexture,position, scale, origin, speed, direction,bullets));
}


void Game::updateMousePos()
{
    //Updates window mouse position(Vector2i)
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies() {
    // Ensure the number of enemies is always `maxEnemies`
    const sf::Vector2f playerPos = this->player->getPosition();
    while (this->enemies.size() < maxEnemies) {
        initEnemy(playerPos);
    }

    // Update enemies
    for (size_t i = 0; i < enemies.size(); i++) {
        enemies[i]->setPlayerPos(playerPos);
        enemies[i]->update();
    }

    // Spawn new enemies based on a timer
    if (clock.getElapsedTime().asSeconds() >= enemySpawnTimerMax) {
        initEnemy(playerPos);
        clock.restart();
    }

    /* Check if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if (!this->mouseHeld) {
            this->mouseHeld = true;
            for (size_t i = 0; i < this->enemies.size(); i++) {
                if (this->enemies[i]->getGlobalBounds().contains(this->mousePosView)) {
                    // Delete enemy
                    enemies.erase(enemies.begin() + i);

                    // Add points
                    this->player->setPoints(this->player->getPoints() + 1);

                    // Spawn a new enemy
                    initEnemy(playerPos);
                    break; // Exit loop after deleting one enemy
                }
            }
        }
    } else {
        this->mouseHeld = false;
    }*/
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
        this->updateMousePos();
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


void Game::renderText(sf::RenderTarget &target) {
    target.draw(this->uiText);
}

void Game::render() {

    //clear frame
    this->window->clear();

    this->player->render(*this->window);
    this->renderText(*this->window);
    /*for (const Bullet* bullet : this->bullets) {
        std::cout << "Rendering bullet at (" << bullet->getPosition().x << ", " << bullet->getPosition().y << ")" << std::endl;
        bullet->render(*window);
    }*/
    //std::cout << bullets.size() << std::endl;
    for (size_t i = 0; i < this->bullets.size(); i++)
    {
        this->bullets[i]->render(*window);
    }
    for (const auto& enemy : this->enemies) {
        enemy->render(*window);
    }
    this->window->display();
}
