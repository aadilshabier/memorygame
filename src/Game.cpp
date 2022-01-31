#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <unordered_map>
#include <cstdlib>
#include <cassert>

#include "Game.h"
#include "Renderer.h"
#include "Square.h"
#include "SDL.h"

namespace MemoryGame
{
	using std::vector;
	using std::cerr;
	using std::find_if;
	using std::unordered_map;

	/* STATIC FUNCTIONS */

	/* check if number is even */
	static bool isEven(int x)
	{
		return (x & 1) == 0;
	}

	/* generate random number k between x and y
	 * x and y inclusive
	 */
	static int randBetween(int x, int y)
	{
		return x + (rand() % (y - x + 1));
	}

	/* generate a vector of x random numbers,
	 * it should contain numbers from 1 to x/2, where each number is present 2 times
	 */
	static vector<int> generateNumbers(int x)
	{
		assert(isEven(x) && "Argument 'x' has to be an even number");

		//use an unordered map to keep track of numbers already inserted
		unordered_map<int, int> counts(x/2);
		for(int i=1; i<=x/2; i++) {
			counts[i] = 2;
		}

		//fill the vector
		vector<int> result(x);
		for(int i=0; i<x; i++) {
			//get random element from counts
			auto it = std::next(std::begin(counts), randBetween(0, counts.size()-1));
			int num = it->first;
			int& count = it->second;
			result[i] = num;
			if(--count == 0)
				counts.erase(it);
		}

		return result;
	}

	/* generate a vector containing x random solid colors (alpha = 255)
	 */
	static vector<SDL_Color> generateColors(int x)
	{
		vector<SDL_Color> result(x);
		for(int i=0; i<x; i++) {
			Uint8 r, g, b, a=255;
			r = randBetween(0, 255);
			g = randBetween(0, 255);
			b = randBetween(0, 255);
			SDL_Color color = {r, g, b, a};
			result[i] = color;
		}

		return result;
	}

	/* CLASS METHODS */

	Game::Game(int nCols, int nRows)
		: mRunning(true)
		, mCols(nCols)
		, mRows(nRows)
		, mSelected(0)
	{
		//Either number of rows and columns have to even
		if(!isEven(nCols) && !isEven(nRows)) {
			cerr << "ERROR: Either nCols or nRows have to be even\n";
			cerr << "nCols: " << nCols << '\n';
			cerr << "nRows: " << nRows << '\n';
			exit(1);
		}

		//seed rng
		srand((unsigned)time(NULL));

		//Generate random numbers
		auto nums = generateNumbers(nCols*nRows);

		//Generate random colors
		auto colors = generateColors((nCols*nRows)/2);

		mSquares.reserve(nCols*nRows);
		for (int i=0; i<nRows; i++) {
			for (int j=0; j<nCols; j++) {
				int x = BORDER_SIZE + (BORDER_SIZE + BOX_SIZE) * j;
				int y = BORDER_SIZE + (BORDER_SIZE + BOX_SIZE) * i;
				int num = nums[i*nCols+j];
				SDL_Color color = colors[num-1];
				mSquares.emplace_back(x, y, BOX_SIZE, BOX_SIZE, num, color);
			}
		}

		int w = BORDER_SIZE + (BORDER_SIZE + BOX_SIZE) * nCols;
		int h = BORDER_SIZE + (BORDER_SIZE + BOX_SIZE) * nRows;
		mRenderer.init("Memory Game", w, h);
	}

	void Game::run()
	{
		uint64_t ticks = SDL_GetTicks64();
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

			//Render only of necessary()
			uint64_t current_ticks = SDL_GetTicks64();
			if ((current_ticks - ticks) >= FRAMERATE_MS) {
				ticks = current_ticks;

				mRenderer.clear();
				mRenderer.drawSquares(mSquares);
				mRenderer.present();
			}
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
			//TODO: game logic
			int tmp = (it - mSquares.begin());
			int x = tmp % mCols;
			int y = tmp / mRows;
			std::cout << "Clicked on box: (" << x << ", " << y << ") containing number " << it->number << '\n';
			//if box is already selected
			if (!it->selected) {
				//if 2 squares are already selected, hide all the other squares and select only this one
				if (mSelected == 2) {
					for(auto& x: mSquares)
						x.selected = false;
					mSelected = 0;
				}
				mSelected++;
			} else {
				mSelected--;
			}
			it->selected = !it->selected;
		}
	}
}
