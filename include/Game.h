#pragma once

#include <vector>
#include <cstdint>

#include "SDL.h"
#include "Renderer.h"
#include "Square.h"

namespace MemoryGame
{
	using std::vector;

	constexpr uint64_t FPS = 60;
	//Framerate in milliseconds
	constexpr uint64_t FRAMERATE_MS = 1000 / FPS;

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
