//
// Created by Marco Otero on 2/3/25.
//
#include "Game.h"

//Private Functions
void Game::initVar() {
    this->window = nullptr;
}

void Game::initWindow() {
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode, "SFML Window",
                                        sf::Style::Titlebar | sf::Style::Close);
}

Game::Game() {
    this->initVar();
    this->initWindow();
}

Game::~Game() {
    delete this->window;
}
//Accessors
bool Game::getIsRunning() const {
    return this->window->isOpen();
}
//Functions

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

void Game::update()
{
    this->pollEvents();
}

void Game::render() {
    this->window->clear(sf::Color::Red);

    //Draw game
    this->window->display();

}
