#pragma once

#include <vector>
#include <cstdint>

#include "SDL.h"
#include "Renderer.h"
#include "Square.h"

namespace MemoryGame
{
	using std::vector;

	constexpr uint64_t FPS = 30;
	//Framerate in milliseconds
	constexpr uint64_t FRAMERATE_MS = 1000 / FPS;

	class Game
	{
	public:
		/* Public instance function */
		static Game* Instance();
		/* Run the game */
		void run();
	private:
		/* Create game grid with given number of squares */
		Game(int nRols, int nRows);
		void handleKeyPress(const SDL_KeyboardEvent& key);
		void handleMouseButtonPress(const SDL_MouseButtonEvent& button);
		// check if the game is won
		bool isWon() const;
	private:
		bool mRunning, mSelected;
		int mCols, mRows;
		int mSolved; // number of solved boxes
		Renderer mRenderer;
		vector<Square> mSquares;
	};
}
