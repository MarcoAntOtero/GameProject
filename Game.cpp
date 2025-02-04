//
// Created by Marco Otero on 2/3/25.
//
#include "Game.h"

//Private Functions
void Game::initVar()
{
    this->window = nullptr;

    //Game Logic
    this->endGame = false;
    this->points = 0;
    this->health = 1000;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;
    this->mouseHeld = false;
}

void Game::initWindow() {
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode, "SFML Window",
                                        sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initText() {
    if (this->font.loadFromFile("/Users/marcootero/CLionProjects/test/Arial.ttf")) {
        std::cerr << "Error loading Arial.ttf" << std::endl;
    }
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(30);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}

/*void Game::initEnemies() {
    this->enemy.setPosition(sf::Vector2f(10.f, 10.f));
    this->enemy.setSize(sf::Vector2(50.f, 50.f));
    this->enemy.setFillColor(sf::Color::Red);

}*/

Game::Game() {
    this->initVar();
    this->initWindow();
    //this->initEnemies();
    this->initText();
}

Game::~Game() {
    delete this->window;
}

//Functions
void Game::spawnEnemy() {
    //Spawn enemies with random pos and random color & adds to vector
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        static_cast<float>(0));
    this->enemy.setSize(sf::Vector2(50.f, 50.f));
    this->enemy.setFillColor(sf::Color::Red);
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

void Game::updateText() {
    std::stringstream ss;
    ss << "Points: " << this->points << std::endl;
    ss << "Health: " << this->health << std::endl;
    this->uiText.setString(ss.str());
}

void Game::update()
{
    this->pollEvents();
    if (!this->endGame) {
        this->updateMousePos();
        this->updateText();
        this->updateEnemies();
    }
    //End game condition after enemies
    if (this->health <= 0) {
        this->endGame = true;
    }
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

        this->enemies[i].move(0.f,5.f);
        //if enemy pressed on then deleted
        if (this->enemies[i].getPosition().y > this->window->getSize().y) {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
        }
    }
    //Check if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (this->mouseHeld == false) {
            this->mouseHeld = true;     //clicks on enemy mouseHeld set to true
            bool deleted = false;
            for (size_t i = 0; i < this->enemies.size() && deleted == false; i++) {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
                    //Delete enemy
                    deleted = true; //break for loop
                    this->enemies.erase(this->enemies.begin() + i);

                    //Add points
                    this->points += 1;
                }
            }
        }
    }
    else {this->mouseHeld = false;} //in the next frame reset to false when left mouse is clicked
}

void Game::renderText(sf::RenderTarget &target)
{
    target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target) {
    for (auto &e : this->enemies) {
        target.draw(e);
    }
}

void Game::render() {

    //clear frame
    this->window->clear();
    //Draw game objects
    this->renderEnemies(*this->window);
    this->renderText(*this->window);
    this->window->display();

}
