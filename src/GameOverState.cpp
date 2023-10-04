#include "Game.h"
#include "GameOverState.h"

namespace MemoryGame
{
	GameOverState::GameOverState()
	{}

	void GameOverState::update()
	{
		for(SDL_Event event; SDL_PollEvent(&event);) {
			switch (event.type) {
			case SDL_QUIT:
				Game::Instance()->setRunning(false);
				break;
			case SDL_KEYDOWN:
				handleKeyPress(event.key);
				break;
			}
		}
	}

	void GameOverState::render(Renderer& /*renderer*/)
	{}

	void GameOverState::onEnter()
	{}

	void GameOverState::onExit()
	{}

	void GameOverState::handleKeyPress(const SDL_KeyboardEvent& key)
	{
		if (key.keysym.sym == SDLK_ESCAPE) {
			Game::Instance()->setRunning(false);
		}
	}

	void handleMouseButtonPress(const SDL_MouseButtonEvent& /*button*/)
	{}
}
