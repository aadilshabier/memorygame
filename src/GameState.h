#pragma once

#include "Renderer.h"

namespace MemoryGame
{
	enum class GameStateType
	{
		MENU_STATE, PLAY_STATE, GAMEOVER_STATE,
	};

	class GameState
	{
	public:
		virtual void update() = 0;
		virtual void render(Renderer& renderer) = 0;

		/* method to run when entering a state */
		virtual void onEnter() = 0;
		/* method to run when exiting a state */
		virtual void onExit() = 0;

		virtual ~GameState() = default;

		virtual GameStateType getStateType() const = 0;
	};
}
