#pragma once

#include "GameState.h"
#include "Renderer.h"
#include "Box.h"

namespace MemoryGame
{
	class PlayState final : public GameState
	{
	public:
		/* Create game grid with given number of boxes */
		PlayState(int nRows, int nCols);

		virtual void update() override;
		virtual void render(Renderer& renderer) override;

		virtual void onEnter() override;
		virtual void onExit() override;

		virtual GameStateType getStateType() const override { return GameStateType::PLAY_STATE; }
	private:
		void handleKeyPress(const SDL_KeyboardEvent& key);
		void handleMouseButtonPress(const SDL_MouseButtonEvent& button);
		/* check if the game is won */
		bool isWon() const;
		/* Draw the given boxes from the vector */
		void drawBoxes(Renderer& renderer);
	private:
		bool mSelected; // if a box was previously selected
		int mCols, mRows;
		int mSolved; // number of solved boxes
		vector<Box> mBoxes;
		int mTilesImg = -1;
	};
	
}
