#pragma once

#include "GameState.h"

namespace MemoryGame
{
	class GameOverState final : public GameState
	{
	public:
		GameOverState();

		/* virtual void update() override; */
		virtual void render(Renderer& renderer) override;

		virtual void onEnter() override;
		virtual void onExit() override;

		virtual GameStateType getStateType() const override { return GameStateType::GAMEOVER_STATE; }
	};
}
