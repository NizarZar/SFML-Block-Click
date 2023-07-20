#include <iostream>
#include "Game.h"


int main() {

	// Init srand
	srand(static_cast<unsigned>(time(NULL)));


	// Init game
	Game game;


	// game loop
	while (game.running() && !game.getEndGame()) {
		
		game.update();
		game.render();
	}
	// end
	return 0;
}