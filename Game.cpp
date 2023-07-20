#include "Game.h"
#include <iostream>

// constructor & destructor
Game::Game() {

	this->initVariables();
	this->initWindow();
	this->initEnemies();

}

Game::~Game() {
	delete this->window;
}


// methods

// initialize variables
void Game::initVariables() {
	this->window = nullptr;

	// game logic
	this->points = 0;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 6;
	this->health = 10;
	this->mouseHeld = false;
	this->gameEnd = false;
	colors[0] = sf::Color::Green;
	colors[1] = sf::Color::Blue;
	colors[2] = sf::Color::Red;

	// resources
	this->font.loadFromFile("Fonts/ARLRDBD.TTF");

	// Text
	this->ui.setFont(this->font);
	this->ui.setCharacterSize(18);
	this->ui.setFillColor(sf::Color::White);
	this->ui.setString("NULL");

}

// initiliaze the window
void Game::initWindow() {
	this->videoMode.width = 800;
	this->videoMode.height = 600;

	this->window = new sf::RenderWindow(this->videoMode, "Block Delete Game", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);

}

void Game::initEnemies() {
	this->enemy.setPosition(15.f,15.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(1.f, 1.f));
	this->enemy.setOutlineThickness(0.05f);

}

// accessors

const bool Game::running() const {

	// check if window is open

	return this->window->isOpen();
}
const bool Game::getEndGame() const {
	return this->gameEnd;
}

void Game::spawnEnemy() {

	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y)
	));

	int randomColor = rand() % (sizeof(colors) / sizeof(colors[0]));
	sf::Color color = colors[randomColor];
	if (color == sf::Color::Green) {
		this->enemy.setFillColor(sf::Color::Green);
		this->enemy.setScale(sf::Vector2f(0.6f, 0.6f));
	}
	else if (color == sf::Color::Blue) {
		this->enemy.setFillColor(sf::Color::Blue);
		this->enemy.setScale(sf::Vector2f(0.3f, 0.3f));
	}
	else if (color == sf::Color::Red) {
		this->enemy.setFillColor(sf::Color::Red);
		this->enemy.setScale(sf::Vector2f(0.1f, 0.1f));
	}
	this->enemies.push_back(this->enemy);
}


void Game::pollEvents() {
	while (this->window->pollEvent(this->event)) {
		switch (this->event.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape) this->window->close();
			break;
		}
	}

}

void Game::updateMousePosition() {

	// updating mouse position of the window
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemy() {
	// updating timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies) {
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else {
			this->enemySpawnTimer += 1.f;
		}
	}

	float moveSpeed = 1.1f;
	// Move enemies
	for (size_t i = 0; i < enemies.size(); i++) {
		this->enemies[i].move(0.f, moveSpeed);
		// if enemy is past y boundaries
		if (this->enemies[i].getPosition().y > this->window->getSize().y) {
			this->enemies.erase(this->enemies.begin() + i);
			health -= 1;
			std::cout << "Current Health: " << this->health << std::endl;
		}
	}
	// Check if enemy is clicked on.
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (!this->mouseHeld) {
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && !deleted; i++) {
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
					deleted = true;
					if (this->enemies[i].getFillColor() == sf::Color::Green) {
						this->points += 1;
					}
					else if (this->enemies[i].getFillColor() == sf::Color::Blue) {
						this->points += 3;
					}
					else if (this->enemies[i].getFillColor() == sf::Color::Red) {
						this->points += 5;
					}
					this->enemies.erase(this->enemies.begin() + i);

				}
			}
		}
	}
	else {
		this->mouseHeld = false;
	}

}

// update game logic
void Game::update() {

	/*
	update game objects and events
	*/
	this->pollEvents();

	if (!this->gameEnd) {
		this->updateEnemy();
		this->updateMousePosition();
	}

	// Text update
	std::stringstream stringStream;
	stringStream << "Points : " << this->points << std::endl << "Health: " << this->health << std::endl;
	this->ui.setString(stringStream.str());


	// end game condition
	if (this->health <= 0) {
		gameEnd = true;
	}


}

// render the visuals 
void Game::render() {

	/*
	Render the game objects
	clear old frame
	display new frames
	*/

	this->window->clear(sf::Color::Black);

	// rendering the enemies
	for (auto& i : this->enemies) {
		this->window->draw(i);
	}

	// text rendering
	this->window->draw(this->ui);


	this->window->display();


}
