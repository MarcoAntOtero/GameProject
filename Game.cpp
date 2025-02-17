//
// Created by Marco Otero on 2/3/25.
//
#include "Game.h"

//Constructor and Destructor
Game::Game() {
    this->initVar();
    this->initPlayer();
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
//Private Functions
void Game::initVar()
{
    //this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Player Survival", sf::Style::Fullscreen);
    //above will not work on macOS

    //Window Variable
    this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Player Survival");
    this->window->setFramerateLimit(FRAMES_PER_SECOND);
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
    this->original = tilesBackGround[4]; //center of 3x3 grid

    //View Variable for window to change depending on player movement
    this->view.setSize(this->window->getSize().x, this->window->getSize().y);
    this->view.zoom(0.3);

    //Game Logic
    this->endGame = false;
}

void Game::initPlayer() {
    //spawns in player
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("Resources/Spaceships/tile007.png"))
        std::cerr << "Error loading Player texture" << std::endl;
    if (!this->healthBarTexture.loadFromFile("Resources/health-meter-02.png")){
        std::cerr << "Failed to load player health bar texture" << std::endl;
    }
    if (!this->healthTexture.loadFromFile("Resources/health-meter-03.png")){
        std::cerr << "Failed to load player health texture" << std::endl;
    }
    const sf::Vector2f position(this->window->getSize().x / 2, this->window->getSize().y / 2);
    const sf::Vector2f scale(1.5, 1.5);
    constexpr float speed = 5.0;
    constexpr float direction = 0.0;

    this->player = new Player(*this->window,playerTexture,position,scale, speed, direction, bullets);

    //Health Bar Variables and Settings
    this->healthBar.setTexture(this->healthBarTexture);
    this->healthBar.setScale(sf::Vector2f(0.5,0.5));
    this->healthBar.setOrigin(this->healthBar.getLocalBounds().width / 2, this->healthBar.getLocalBounds().height / 2);
    this->healthBar.setPosition(200,100); //position to be in

    this->health.setTexture(this->healthTexture);
    this->health.setScale(sf::Vector2f(0.5,0.5));
    this->health.setOrigin(this->health.getLocalBounds().width / 2, this->health.getLocalBounds().height / 2);
    this->health.setPosition(this->healthBar.getPosition());
    this->fullHealthWidth = healthTexture.getSize().x; // Full width of the health texture needed for increasing health
}
//Used in updateEnemies func
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
    const sf::Vector2f scale(1.5, 1.5);
    constexpr float speed = 5.0;
    constexpr float direction = 0.0;
    this->enemies.push_back(new Enemy(enemyTexture,position, scale, speed, direction,bullets));
}
//Called in updateBullets
void Game::checkCollision() {
    for (size_t i = this->bullets.size(); i-- > 0;) //
    {
        if (bullets[i]->getGlobalBounds().intersects(this->player->getGlobalBounds())
            && !bullets[i]->getPlayerBullet())
        {
            this->player->setHealth(this->player->getHealth() - bullets[i]->getBulletDamage());
            delete bullets[i];
            bullets.erase(bullets.begin() + i);

        }
        for (size_t j = 0; j < enemies.size(); j++)
        {
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
//Used in updateTiles func
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
/*
 *
 *  Update Functions
 *
 *
 *
 *
 *
 *
 */
//Check if window closed before going into rest of update functions
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
    for (int i = tilesBackGround.size() - 1; i >= 0; i--) //reverse loop cuz deleting elements in vector
        {
        float distanceX = std::abs(tilesBackGround[i]->getPosition().x - playerPos.x);//get current distance
        float distanceY = std::abs(tilesBackGround[i]->getPosition().y - playerPos.y);
        float maxDistanceX = this->window->getSize().x;//max distance is one window away
        float maxDistanceY = this->window->getSize().y;
        if (distanceX > maxDistanceX || distanceY > maxDistanceY)
        {
            delete tilesBackGround[i];
            tilesBackGround.erase(tilesBackGround.begin() + i);
        }
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

void Game::updateBullets() {
    for (size_t i = this->bullets.size(); i-- > 0;) {
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
            if (this->player->getHealth() < MAX_PLAYER_HEALTH) {
                this->player->setHealth(this->player->getHealth() + 10);
            }

        }
    }

}


void Game::updateView() {
    this->view.setCenter(player->getPosition());
    this->window->setView(view);
}

void Game::updateHealthBar() {
    float playerHealthPercent = static_cast<float>(this->player->getHealth()) / MAX_PLAYER_HEALTH;
    this->health.setTextureRect(sf::IntRect(0,0,
        static_cast<int>(fullHealthWidth * playerHealthPercent),this->health.getLocalBounds().height));
}

//Hold all update functions
void Game::update()
{
    //all update functions
    this->pollEvents();
    if (!this->endGame) {
        this->updateView();
        this->updateTiles(this->player->getPosition());
        this->updateBullets();
        this->updateEnemies();
        this->updateHealthBar();
        this->player->update();
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

void Game::renderHealthBar(sf::RenderTarget &target) {
    sf::View currentView = this->window->getView(); //get zoomed in view
    this->window->setView(this->window->getDefaultView()); //make the window original size
    target.draw(this->healthBar);                       //drawGUI elements
    target.draw(this->health);
    this->window->setView(currentView); //reset to zoomed in view so game appears as normal
}

void Game::render() {

    //clear frame
    this->window->clear();
    this->renderBackground(*this->window);
    this->renderHealthBar(*this->window);
    this->player->render(*this->window);
    for (size_t i = 0; i < this->bullets.size(); i++)
    {
        this->bullets[i]->render(*window);
    }
    for (const auto& enemy : this->enemies) {
        enemy->render(*window);
    }
    this->window->display();
}
