#pragma once

#include <vector>

#include "SDL.h"
#include "Renderer.h"
#include "Square.h"

namespace MemoryGame
{
	using std::vector;

	class Game
	{
	public:
		/* Create game grid with given number of squares */
		Game(int nRols, int nRows);
		/* Run the game */
		void run();
	private:
		void handleKeyPress(const SDL_KeyboardEvent& key);
		void handleMouseButtonPress(const SDL_MouseButtonEvent& button);
	private:
		bool mRunning;
		int mCols, mRows;
		Renderer mRenderer;
		vector<Square> mSquares;
	};
}
