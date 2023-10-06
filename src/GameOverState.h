#pragma once

#include "GameState.h"

namespace MemoryGame
{
	class GameOverState final : public GameState
	{
	public:
		GameOverState();

		virtual void update() override;
		virtual void render(Renderer& renderer) override;

		virtual void onEnter() override;
		virtual void onExit() override;

		virtual GameStateType getStateType() const override { return GameStateType::GAMEOVER_STATE; }
	private:
		void handleKeyPress(const SDL_KeyboardEvent& key);
		void handleMouseButtonPress(const SDL_MouseButtonEvent& button);
	private:
		int mGameOverImg = -1; // texture ID of "Game Over" Image
	};
}
