#include <cstdint>

#include "Config.h"
#include "Game.h"
#include "Renderer.h"
#include "SDL.h"
#include "PlayState.h"

namespace MemoryGame
{
	/* CLASS METHODS */

	//static instance
	static Game* sGame = nullptr;

	Game* Game::Instance()
	{
		if(sGame == nullptr)
			sGame = new Game();
		return sGame;
	}

	Game::Game()
		: mRunning(true)
	{
		mRenderer.init("Memory Game", W, H);
	}

	void Game::run()
	{
		//TODO: Change initial state to MenState
		mGameStateMachine.pushState(new PlayState(Y, X));

		uint64_t ticks = SDL_GetTicks64();
		while (mRunning) {
			mGameStateMachine.update();

			mRenderer.clear();
			mGameStateMachine.render(mRenderer);
			mRenderer.present();

			//sleep off the remaining time
			int64_t diff = FRAMERATE_MS - (SDL_GetTicks64() - ticks);
			if (diff > 0) {
				ticks = SDL_GetTicks64();
				SDL_Delay(diff);
			}
		}		
	}
}
