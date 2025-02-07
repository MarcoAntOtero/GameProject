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
    this->mouseHeld = false;
}

void Game::initWindow() {
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode, "SFML Window",
                                        sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}
/*
void Game::initText() {
    if (this->font.loadFromFile("/Users/marcootero/CLionProjects/test/Arial.ttf")) {
        std::cerr << "Error loading Arial.ttf" << std::endl;
    }
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(30);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}
*/
/*void Game::initEnemies() {
    this->enemy.setPosition(sf::Vector2f(10.f, 10.f));
    this->enemy.setSize(sf::Vector2(50.f, 50.f));
    this->enemy.setFillColor(sf::Color::Red);

}*/

Game::Game() {
    this->initVar();
    this->initWindow();
    //this->initEnemies();
    //this->initText();
}

Game::~Game() {
    delete this->window;
    for (int i = 0; i < enemies.size(); i++) {
        delete enemies.at(i);
    }
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

void Game::spawnEnemy() {

    const float x = rand() % this->window->getSize().x - this->window->getSize().x / 2;
    const float y = rand() % this->window->getSize().y - this->window->getSize().y / 2;
    this->enemies.push_back(new Enemy(sf::Vector2(x,y)));

}

void Game::updateMousePos()
{
    //Updates window mouse position(Vector2i)
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies() {
    if (this->enemies.size() < maxEnemies) {
        //if equals maxSpawnTimer spawn new enemy and reset time
        if (clock.getElapsedTime().asMicroseconds() >= enemySpawnTimerMax) {
            spawnEnemy();
            clock.restart();
        }
    }
    //Enemy movement
    for (size_t i = 0; i < enemies.size(); i++) {

        //simple move down
        enemies.at(i)->updateEnemy();
        //if enemy pressed on then deleted
        if (enemies.at(i)->getPosition().y > this->window->getSize().y) {
            delete enemies.at(i);
            this->enemies.erase(this->enemies.begin() + i);
            this->player.setHealth(player.getHealth() - 1);
        }
    }
    //Check if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (this->mouseHeld == false) {
            this->mouseHeld = true;     //clicks on enemy mouseHeld set to true
            bool deleted = false;
            for (size_t i = 0; i < this->enemies.size() && deleted == false; i++) {
                if (this->enemies[i]->getGlobalBounds().contains(this->mousePosView)) {
                    //Delete enemy
                    deleted = true; //break for loop
                    delete enemies.at(i);
                    this->enemies.erase(this->enemies.begin() + i);
                    spawnEnemy();

                    //Add points
                    unsigned points = this->player.getPoints();  // Get the current points
                    points += 1;                            // Increment
                    this->player.setPoints(points);
                }
            }
        }
    }
    else {this->mouseHeld = false;} //in the next frame reset to false when left mouse is clicked
}


/*void Game::updateText() {
    std::stringstream ss;
    ss << "Points: " << this->Player.getPoints << std::endl;
    ss << "Health: " << this->health << std::endl;
    this->uiText.setString(ss.str());
}*/
void Game::update()
{
    //all update functions
    this->pollEvents();
    if (!this->endGame) {
        this->updateMousePos();
        //this->updateText();
        this->player.updatePlayer();
        this->updateEnemies();
    }
    //End game condition after enemies
    if (this->player.getHealth() <= 0) {
        this->endGame = true;
    }
}
/*
 *
 *RENDER FUNCTIONS
 *
 *
 */



void Game::renderEnemies(sf::RenderTarget& target) const {
    for (const auto& e : this->enemies) {
        e->renderEnemy(target);
    }
}

void Game::render() {

    //clear frame
    this->window->clear();
    //Draw game objects
    this->renderEnemies(*this->window);
    this->player.renderPlayer(*this->window);
    //this->renderText(*this->window);

    this->window->display();


}
