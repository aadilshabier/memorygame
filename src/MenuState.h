#pragma once

#include "GameState.h"

namespace MemoryGame
{
	class MenuState final : public GameState
	{
	public:
		virtual void update() override;
		virtual void render(Renderer& renderer) override;

		virtual void onEnter() override;
		virtual void onExit() override;

		virtual GameStateType getStateType() const override { return GameStateType::MENU_STATE; }
	};
}
