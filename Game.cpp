//
// Created by Marco Otero on 2/3/25.
//
#include "Game.h"

//Private Functions
void Game::initVar()
{
    this->window = nullptr;

    //Game Logic
    this->points = 0;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;
}

void Game::initWindow() {
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode, "SFML Window",
                                        sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initEnemies() {
    this->enemy.setPosition(sf::Vector2f(10.f, 10.f));
    this->enemy.setSize(sf::Vector2(50.f, 50.f));
    this->enemy.setFillColor(sf::Color::Cyan);

}

Game::Game() {
    this->initVar();
    this->initWindow();
    this->initEnemies();
}

Game::~Game() {
    delete this->window;
}
//Accessors
bool Game::getIsRunning() const {
    return this->window->isOpen();
}

//Functions
void Game::spawnEnemy() {
    //Spawn enemies with random pos and random color & adds to vector
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y)));

    this->enemy.setFillColor(sf::Color::Green);
    this->enemies.push_back(this->enemy);
}


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

void Game::updateMousePos()
{
    //Updates window mouse position(Vector2i)
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::update()
{
    this->pollEvents();
    this->updateMousePos();
    this->updateEnemies();
}

void Game::updateEnemies()
{
    //Updates timer for enemy spawning
    if (this->enemies.size() < this->maxEnemies) {
        //if equals maxSpawnTimer spawn new enemy and reset time
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        //slowly increments spawn of enemySpawnTimer until reaches mas
        else {
            this->enemySpawnTimer += 1.f;
        }
    }
    //Enemy movement
    for (int i = 0; i < this->enemies.size(); i++) {
        bool deleted = false;

        this->enemies[i].move(0.f,5.f);
        //if enemy pressed on then deleted
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
                deleted = true;
                this->points +=  10;
            }
        }
        //if enemy past bottom screen delete
        if (this->enemies[i].getPosition().y > this->window->getSize().y) {
            deleted = true;
            this->points += 10;
        }
        //Final delete
        if (deleted) {
            this->enemies.erase(this->enemies.begin() + i);
        }
    }
}

void Game::renderEnemies() {
    for (auto &e : this->enemies) {
        this->window->draw(e);
    }
}

void Game::render() {
    //clear frame
    this->window->clear();

    //Draw game objects
    this->renderEnemies();

    this->window->display();

}
