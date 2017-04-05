#include <SFML/Graphics.hpp>
#include "ClientNetwork.h"
#include "GameClient.h"
#include <Game\Player.h>

int main()
{
	std::unique_ptr<GameClient> client (new GameClient());
	/* Creates a thread of the draw function so it can run
		with other tasks instead of halting the game. */
		//Runs the draw thread
	client->initialise();
		/* connects to the server */
		return 0;
}