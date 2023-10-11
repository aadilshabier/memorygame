#include "Config.h"
#include "Game.h"
#include "GameOverState.h"
#include "TextureManager.h"
#include "PlayState.h"

namespace MemoryGame
{
	const char* GAME_OVER_FILE = "assets/game_over3.png";

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

	void GameOverState::render(Renderer& renderer)
	{
		auto* texture = TextureManager::Instance()->get(mGameOverImg);
		renderer.drawTexture(texture, nullptr, nullptr);
	}

	void GameOverState::onEnter()
	{
		auto* renderer = Game::Instance()->mRenderer.mRenderer;
		mGameOverImg = TextureManager::Instance()->load(GAME_OVER_FILE, renderer);
		if (mGameOverImg == -1) {
			exit(1);
		}
	}

	void GameOverState::onExit()
	{
		TextureManager::Instance()->unload(mGameOverImg);
		mGameOverImg = -1;
	}

	void GameOverState::handleKeyPress(const SDL_KeyboardEvent& key)
	{
		if (key.keysym.sym == SDLK_ESCAPE) {
			Game::Instance()->setRunning(false);
		} else if (key.keysym.sym == SDLK_r) {
			Game::Instance()->getStateMachine()->changeState(new PlayState(Y, X));
		}
	}

	void handleMouseButtonPress(const SDL_MouseButtonEvent& /*button*/)
	{}
}
