#include <vector>
#include <cstdlib>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <cassert>

#include "SDL.h"
#include "Game.h"
#include "PlayState.h"
#include "GameOverState.h"

namespace MemoryGame
{
	using std::vector;
	using std::cerr;
	using std::find_if;
	using std::unordered_map;

	constexpr int BOX_SIZE = 100;
	constexpr int BORDER_SIZE = 20;

	constexpr SDL_Color DEFAULT_BOX_COLOR = {255, 255, 255, 255}; // white


	/* STATIC FUNCTIONS */

	/* check if number is even */
	static inline bool isEven(int x)
	{
		return (x & 1) == 0;
	}

	/* generate random number k between x and y
	 * x and y inclusive
	 */
	static inline int randBetween(int x, int y)
	{
		return x + (rand() % (y - x + 1));
	}

	/* generate a vector of x random numbers,
	 * it should contain numbers from 1 to x/2, where each number is present 2 times
	 */
	static vector<int> generateNumbers(int x)
	{
		assert(isEven(x));

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

	PlayState::PlayState(int nRows, int nCols)
		: mSelected(false)
		, mCols(nCols)
		, mRows(nRows)
		, mSolved(0)
	{
		//Either number of rows and columns have to be even
		if(!isEven(nCols) && !isEven(nRows)) {
			cerr << "ERROR: Either nCols or nRows have to be even\n";
			cerr << "nCols: " << nCols << '\n';
			cerr << "nRows: " << nRows << '\n';
			exit(1);
		}
	}

	void PlayState::update()
	{
		for(SDL_Event event; SDL_PollEvent(&event);) {
			switch (event.type) {
			case SDL_QUIT:
				Game::Instance()->setRunning(false);
				break;
			case SDL_KEYDOWN:
				handleKeyPress(event.key);
				break;
			case SDL_MOUSEBUTTONDOWN:
				handleMouseButtonPress(event.button);
				break;
			}
		}

		if (isWon()) {
			Game::Instance()->getStateMachine()->changeState(new GameOverState());
		}
	}

	void PlayState::render(Renderer& renderer)
	{
		drawSquares(renderer);
	}

	void PlayState::onEnter()
	{	
		//seed rng
		srand((unsigned)time(NULL));

		//Generate random numbers
		auto nums = generateNumbers(mCols*mRows);

		//Generate random colors
		auto colors = generateColors((mCols*mRows)/2);

		mSquares.reserve(mCols*mRows);
		for (int i=0; i<mRows; i++) {
			for (int j=0; j<mCols; j++) {
				int x = BORDER_SIZE + (BORDER_SIZE + BOX_SIZE) * j;
				int y = BORDER_SIZE + (BORDER_SIZE + BOX_SIZE) * i;
				int num = nums[i*mCols+j];
				SDL_Color color = colors[num-1];
				mSquares.emplace_back(x, y, BOX_SIZE, BOX_SIZE, num, color);
			}
		}
	}

	void PlayState::onExit()
	{}

	void PlayState::handleKeyPress(const SDL_KeyboardEvent& key)
	{
		if (key.keysym.sym == SDLK_ESCAPE) {
			Game::Instance()->setRunning(false);
		}
	}

	void PlayState::handleMouseButtonPress(const SDL_MouseButtonEvent& button)
	{
		// get the select box
		auto it = find_if(mSquares.begin(), mSquares.end(), [&button](const Box& x) {
			return x.containsCoords(button.x, button.y);
		});

		// if not found, leave
		if(it == mSquares.end()) {
			return;
		}

		//game logic
		//if box is already selected unselect it
		if (it->selected) {
			mSelected = false;
			it->selected = false;
		} else {
			// check if no other square was selected first
			if (!mSelected) {
				mSelected = true;
				it->selected = true;
			} else  {
				// get the other selected box
				auto selectedBox = find_if(mSquares.begin(), mSquares.end(), [&](const Box& x) {
					return x.selected;
				});
				// if the colors of the boxes match, mark it solved
				if(it->number == selectedBox->number) {
					it->solved = true;
					selectedBox->solved = true;
					it->selected = false;
					selectedBox->selected = false;
					mSelected = false;
					mSolved += 2;
				} else {
					selectedBox->selected = false;
					it->selected = true;
				}
			}
		}
	}

	bool PlayState::isWon() const
	{
		assert(!(mSolved > mRows * mCols));
		return(mSolved == mRows * mCols);
	}

	void PlayState::drawSquares(Renderer& renderer)
	{
		for(const auto& x: mSquares) {
			SDL_Color color = (x.solved || x.selected) ? x.color : DEFAULT_BOX_COLOR;
			renderer.drawRect(color, &x.rect);
		}
	}
}
