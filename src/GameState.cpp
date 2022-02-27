#include "GameState.h"
#include "Game.h"
#include "SDL.h"

namespace MemoryGame
{
	void GameState::update()
	{
		for(SDL_Event event; SDL_PollEvent(&event); ) {
			switch (event.type) {
			case SDL_QUIT:
				Game::Instance()->setRunning(false);
				break;
			}
		}
	}
}
