#pragma once

#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
		Game wrapper class 
*/

class Game
{
private:
	// variables
	sf::RenderWindow* window;
	sf::Event event;
	sf::VideoMode videoMode;

	// Game Logic
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	unsigned points;
	int maxEnemies;
	bool mouseHeld;
	bool gameEnd;
	int health;


	// Resources
	sf::Font font;


	// Text
	sf::Text ui;


	// Game Objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;
	sf::Color colors[3];

	// Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;


	// private methods
	void initVariables();
	void initWindow();
	void initEnemies();
	


public:

	// Constructor & Destructor
	Game();
	virtual ~Game();

	// Accessors
	const bool running() const;
	const bool getEndGame() const;

	// Methods
	void spawnEnemy();
	void updateEnemy();
	void pollEvents();
	void update();
	void updateMousePosition();
	void render();


};