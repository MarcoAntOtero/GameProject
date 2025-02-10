//
// Created by Marco Otero on 2/3/25.
//
#include "Game.h"

//Private Functions
void Game::initVar()
{
    //Window Variable
    this->window = nullptr;
    this->window = new sf::RenderWindow({2560,1664}, "SFML Window");
    this->window->setFramerateLimit(60);
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
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(30);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}

void Game::initPlayer() {
    //spawns in player
    this->player.setPosition(this->window->getSize().x / 2, this->window->getSize().y / 2);
    //sprite is 16x16 so origin must be set at 8,8
    this->player.setOrigin(8, 8);

}

/*void Game::initEnemies() {
    this->enemy.setPosition(sf::Vector2f(10.f, 10.f));
    this->enemy.setSize(sf::Vector2(50.f, 50.f));
    this->enemy.setFillColor(sf::Color::Red);

}*/

Game::Game() {
    this->initVar();
    this->initPlayer();
    this->initText();
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

void Game::spawnEnemy(sf::Vector2f playerPos) {

    std::random_device rdx;
    std::mt19937 genx(rdx());
    std::uniform_int_distribution<int> distx(playerPos.x - (this->window->getSize().x / 2.f),
                                            playerPos.x + (this->window->getSize().x / 2.f));

    std::random_device rdy;
    std::mt19937 geny(rdy());
    std::uniform_int_distribution<int> disty(playerPos.y - (this->window->getSize().y / 2.f),
                                            playerPos.y + (this->window->getSize().y / 2.f));

    const float x = static_cast<float>(distx(genx));
    const float y = static_cast<float>(disty(geny));
    this->enemies.push_back(new Enemy(sf::Vector2(x,y)));

}


void Game::updateMousePos()
{
    //Updates window mouse position(Vector2i)
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies() {
    // Ensure the number of enemies is always `maxEnemies`
    while (this->enemies.size() < maxEnemies) {
        spawnEnemy(this->player.getPosition());
    }

    //Enemy movement
    for (int i = enemies.size() - 1; i >= 0; i--) {
        if (enemies.at(i) != nullptr) {    //have to check if not nullptr
            enemies.at(i)->updateEnemy(this->player.getPosition());

            /* If enemy moves off-screen, delete it
            if (enemies[i]->getPosition().y > this->window->getSize().y) {
                delete enemies[i];   // Free memory
                enemies[i] = nullptr; // Prevent dangling pointer
                enemies.erase(enemies.begin() + i);
                this->player.setHealth(player.getHealth() - 1);
            }*/
        }
    }

    //if equals maxSpawnTimer spawn new enemy and reset time
    if (clock.getElapsedTime().asSeconds() >= enemySpawnTimerMax)
    {
        spawnEnemy(this->player.getPosition());
        clock.restart();
    }

    //Check if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->mouseHeld == false)
        {
            this->mouseHeld = true;     //clicks on enemy mouseHeld set to true
            bool deleted = false;

            for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
            {
                if (this->enemies.at(i)->getGlobalBounds().contains(this->mousePosView)) {
                    //Delete enemy
                    deleted = true; //break for loop
                    delete enemies.at(i);
                    enemies.at(i) = nullptr;
                    this->enemies.erase(this->enemies.begin() + i);

                    //AddPoints
                    this->player.setPoints(player.getPoints() + 1);

                    spawnEnemy(this->player.getPosition());
                }
            }
        }
    }
    else {this->mouseHeld = false;} //in the next frame reset to false when left mouse is clicked
}


void Game::updateText() {
    std::stringstream ss;
    ss << "Points: " << this->player.getPoints() << std::endl;
    ss << "Health: " << this->player.getHealth() << std::endl;
    this->uiText.setString(ss.str());
}

void Game::updateView() {
    this->view.setCenter(player.getPosition());
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
        this->player.updatePlayer(*this->window);
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

void Game::renderText(sf::RenderTarget &target) {
    target.draw(this->uiText);
}

void Game::render() {

    //clear frame
    this->window->clear();
    //Draw game objects
    this->renderEnemies(*this->window);
    this->player.renderPlayer(*this->window);
    this->renderText(*this->window);

    this->window->display();


}
