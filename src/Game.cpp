#include <iostream>
#include <vector>
#include <algorithm>

#include "Game.h"
#include "Renderer.h"
#include "Square.h"
#include "SDL.h"

namespace MemoryGame
{
	using std::vector;
	using std::cerr;
	using std::find_if;

	/* STATIC FUNCTIONS */

	/* check if number is even */
	static bool isEven(int x)
	{
		return (x & 1) == 0;
	}

	/* CLASS METHODS */
	
	Game::Game(int nCols, int nRows)
		: mRunning(true)
		, mCols(nCols)
		, mRows(nRows)
	{
		//either number of rows and columns have to even
		if(!isEven(nCols) && !isEven(nRows)) {
			cerr << "ERROR: Either nCols or nRows have to be even\n";
			cerr << "nCols: " << nCols << '\n';
			cerr << "nRows: " << nRows << '\n';
			exit(1);
		}

		mSquares.reserve(nCols*nRows);
		for (int i=0; i<nRows; i++) {
			for (int j=0; j<nCols; j++) {
				int x = BORDER_SIZE + (BORDER_SIZE + BOX_SIZE) * j;
				int y = BORDER_SIZE + (BORDER_SIZE + BOX_SIZE) * i;
				mSquares.emplace_back(x, y, BOX_SIZE, BOX_SIZE, 0);
			}
		}

		int w = BORDER_SIZE + (BORDER_SIZE + BOX_SIZE) * nCols;
		int h = BORDER_SIZE + (BORDER_SIZE + BOX_SIZE) * nRows;
		mRenderer.init("Memory Game", w, h);
	}

	void Game::run()
	{
		while (mRunning) {
			for(SDL_Event event; SDL_PollEvent(&event);) {
				switch (event.type) {
				case SDL_QUIT:
					mRunning = false;
					break;
				case SDL_KEYDOWN:
					handleKeyPress(event.key);
					break;
				case SDL_MOUSEBUTTONDOWN:
					handleMouseButtonPress(event.button);
					break;
				}
			}

			mRenderer.clear();

			//TODO: do stuff here
			mRenderer.drawSquares(mSquares);

			mRenderer.present();
		}	
	}

	void Game::handleKeyPress(const SDL_KeyboardEvent& key)
	{
		if (key.keysym.sym == SDLK_ESCAPE) {
			mRunning = false;
		}
	}

	void Game::handleMouseButtonPress(const SDL_MouseButtonEvent& button)
	{
		auto it = find_if(mSquares.begin(), mSquares.end(), [&](Square x) {
			return x.containsCoords(button.x, button.y);
		});

		if(it != mSquares.end()) {
			int tmp = (it-mSquares.begin());
			int x = tmp % mCols;
			int y = tmp / mRows;
			std::cout << "Clicked on box: (" << x << ", " << y << ")\n";
		}
	}
}
