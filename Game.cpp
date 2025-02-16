//
// Created by Marco Otero on 2/3/25.
//
#include "Game.h"

#include <iostream>

//Private Functions
void Game::initVar()
{
    //this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Player Survival", sf::Style::Fullscreen);
    //above will not work on macOS

    //Window Variable
    this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Player Survival");
    this->window->setFramerateLimit(60);
    this->player = nullptr;

    //Initializing Background
    /*
     * 0 3 6
     * 1 4 7
     * 2 5 8
     */
    this->backGroundTexture.loadFromFile("Resources/SpaceBackground.png");
    this->tileSize.x = this->window->getSize().x;
    this->tileSize.y = this->window->getSize().y;

    for (int x = -1; x < 2; x++)
    {
        for (int y = -1; y < 2; y++)
        {
            sf::RectangleShape* tile = new sf::RectangleShape(this->tileSize);
            tile->setPosition(static_cast<float>(x) * tileSize.x, static_cast<float>(y) * tileSize.y);
            tile->setTexture(&backGroundTexture);
            tilesBackGround.push_back(tile);
        }
    }
    this->original = tilesBackGround[4]; //center 3x3

    //View Variable for window to change depending on player movement
    this->view.setSize(this->window->getSize().x, this->window->getSize().y);
    this->view.zoom(0.3);

    //Game Logic
    this->endGame = false;
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
    const sf::Vector2f scale(2.0, 2.0);
    constexpr float speed = 6.0;
    constexpr float direction = 0.0;

    this->player = new Player(*this->window,playerTexture,position,scale, speed, direction, bullets);
}

Game::Game() {
    this->initVar();
    this->initPlayer();
    this->initText();
}

Game::~Game() {
    delete this->window;
    for (const auto &tile : tilesBackGround)
    {
        delete tile;
    }
    for (const auto &bullet : bullets)
    {
        delete bullet;
    }
    for (const auto &enemy : enemies)
    {
        delete enemy;
    }
    delete this->player;

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
        if (bullets[i]->getGlobalBounds().intersects(this->player->getGlobalBounds())
            && !bullets[i]->getPlayerBullet())
        {
            this->player->setHealth(this->player->getHealth() - bullets[i]->getBulletDamage());
            delete bullets[i];
            bullets.erase(bullets.begin() + i);

        }
        for (size_t j = 0; j < enemies.size(); j++) {
            if (!this->enemies[j]->getHealth() > 0){this->enemies[j]->setToBeDestroyed(true);}
            else if (bullets[i]->getGlobalBounds().intersects(enemies[j]->getGlobalBounds())
                && bullets[i]->getPlayerBullet())
            {
                this->enemies[j]->setHealth(this->enemies[j]->getHealth() - bullets[i]->getBulletDamage());
                delete bullets[i];      //delete bullet when intersects and lower enemy health
                bullets.erase(bullets.begin() + i);

            }
        }
    }
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
    const sf::Vector2f scale(2.0, 2.0);
    constexpr float speed = 5.5;
    constexpr float direction = 0.0;
    this->enemies.push_back(new Enemy(enemyTexture,position, scale, speed, direction,bullets));
}

/*
 *
 *
 *
 *Update FUNCTIONs
 *
 *
 *
 */

void Game::updateTiles(sf::Vector2f playerPos)
{
    //Check if player has moved from original tile
    if (this->original->getGlobalBounds().contains(playerPos)) {return;}

    sf::RectangleShape* current = nullptr;
    for (int i = 0; i < tilesBackGround.size(); i++)
    {
        if (tilesBackGround[i]->getGlobalBounds().contains(playerPos)) {current = tilesBackGround[i];}
    }

    //Delete for loops
    std::vector<int> toBeDeleted;
    for (int i = 0; i < tilesBackGround.size(); i++)
        {
        float distanceX = std::abs(tilesBackGround[i]->getPosition().x - playerPos.x);
        float distanceY = std::abs(tilesBackGround[i]->getPosition().y - playerPos.y);
        float maxDistanceX = this->window->getSize().x;
        float maxDistanceY = this->window->getSize().y;
        if (distanceX > maxDistanceX || distanceY > maxDistanceY){toBeDeleted.push_back(i);}
    }
    for (int i = toBeDeleted.size() - 1; i >= 0; i--)
    {
        delete tilesBackGround[toBeDeleted[i]];
        tilesBackGround.erase(tilesBackGround.begin() + toBeDeleted[i]);
    }

    //Add tiles for loops
    for (int x = -1; x < 2; x++)
    {
        for (int y = -1; y < 2; y++)
        {
            sf::Vector2f newTilePosition((static_cast<float>(x) * tileSize.x + current->getPosition().x),
                (static_cast<float>(y) * tileSize.y + current->getPosition().y));
            if (!alreadyTile(newTilePosition)) {
                sf::RectangleShape* tile = new sf::RectangleShape(this->tileSize);
                tile->setTexture(&backGroundTexture);
                tile->setPosition(newTilePosition);
                tilesBackGround.push_back(tile);
            }
        }
    }

    this->original = current;
}

bool Game::alreadyTile(sf::Vector2f newTilePosition) {
    for (int i = 0; i < tilesBackGround.size(); i++) {
        if (newTilePosition.x == tilesBackGround[i]->getPosition().x
            && newTilePosition.y == tilesBackGround[i]->getPosition().y)
        {
            return true;
        }
    }
    return false;
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

void Game::updateEnemies() {
    // Ensure the number of enemies is always `maxEnemies`
    while (this->enemies.size() < maxEnemies && this->enemyTimer.getElapsedTime().asSeconds() >= enemySpawnTimerMax) {
        initEnemy(this->player->getPosition()); //adds enemy to vector
        this->enemyTimer.restart();
    }

    // Update enemies, where they move and aim and if they are to be destroyed, backwards loop because
    //deleting items in vector while iterating through it
    for (int i = enemies.size() - 1; i >= 0 ; i--)
    {
        enemies[i]->setPlayerPos(this->player->getPosition());
        enemies[i]->update();
        //Destroy animation
        if (this->enemies[i]->getToBeDestroyed()) { //only if health is less than 0
            // Delete enemy
            if (!this->enemies[i]->isAnimationDone()) {
                this->enemies[i]->destroyed(); //destruction animation
                continue; //move to next iteration and do not delete
            }
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

//Hold all update functions
void Game::update()
{
    //all update functions
    this->pollEvents();
    if (!this->endGame) {
        this->updateText();
        this->updateView();
        this->player->update(); // Update player first
        this->updateTiles(this->player->getPosition());
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
    for (int i = 0; i < this->tilesBackGround.size(); i++) {
        target.draw(*this->tilesBackGround[i]);
    }
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
