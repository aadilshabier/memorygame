#include <vector>
#include <cstdlib>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <random>

#include "SDL.h"
#include "Game.h"
#include "GameOverState.h"
#include "PlayState.h"
#include "TextureManager.h"

namespace MemoryGame
{
	using std::vector;
	using std::cerr;
	using std::find_if;
	using std::unordered_map;

	const char* TILES_FILE = "assets/tiles1.jpg";

	constexpr int TILES_M = 10;
	constexpr int TILES_N = 8;

	constexpr int TILES_START = 19;
	constexpr int TILES_SIZE = 89;
	constexpr int TILES_OFFSET = 8;

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

	/* generate a vector of x random numbers in the range [0, max)
	 */
	static vector<int> generateNumbers(int x, int max)
	{
		assert(max >= x);

		vector<int> result(max);
		for (int i=0; i<max; i++) {
			result[i] = i;
		}

		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(result.begin(), result.end(), g);
		result.resize(x);

		return result;
	}

	/* Return a vector<int> which contains every element of nums twice
	 * and shuffled
	 */
	static vector<int> generatePositions(const vector<int>& nums) {
		vector<int> result(nums);
		auto size = result.size();
		for (size_t i=0; i<size; i++) {
		    result.push_back(result[i]);
		}
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(result.begin(), result.end(), g);
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
		drawBoxes(renderer);
	}

	void PlayState::onEnter()
	{	
		// seed rng
		srand((unsigned)time(NULL));

		// Generate x unique numbers within the range [0, max)
		auto nums = generateNumbers(mCols*mRows/2, TILES_M*TILES_N);

		// Generate positions of the textures on the boards
		auto positions = generatePositions(nums);

		auto* renderer = Game::Instance()->mRenderer.mRenderer;
	    mTilesImg = TextureManager::Instance()->load(TILES_FILE, renderer);
		if (mTilesImg == -1) {
			exit(1);
		}

		mBoxes.reserve(mCols*mRows);
		for (int i=0; i<mRows; i++) {
			for (int j=0; j<mCols; j++) {
				SDL_Rect windowRect, textureRect;

				windowRect.x = BORDER_SIZE + (BORDER_SIZE + BOX_SIZE) * j;
				windowRect.y = BORDER_SIZE + (BORDER_SIZE + BOX_SIZE) * i;
				windowRect.w = BOX_SIZE;
				windowRect.h = BOX_SIZE;

				int boxIdx = i*mCols+j;
				int number = positions[boxIdx];
				int pos_i = number % TILES_M;
				int pos_j = number / TILES_M;
				textureRect.x = TILES_START + (TILES_SIZE + TILES_OFFSET) * pos_i;
				textureRect.y = TILES_START + (TILES_SIZE + TILES_OFFSET) * pos_j;
				textureRect.w = TILES_SIZE;
				textureRect.h = TILES_SIZE;

				mBoxes.emplace_back(windowRect, textureRect, number);
			}
		}
	}

	void PlayState::onExit()
	{
		TextureManager::Instance()->unload(mTilesImg);
		mTilesImg = -1;
	}

	void PlayState::handleKeyPress(const SDL_KeyboardEvent& key)
	{
		if (key.keysym.sym == SDLK_ESCAPE) {
			Game::Instance()->setRunning(false);
		}
	}

	void PlayState::handleMouseButtonPress(const SDL_MouseButtonEvent& button)
	{
		// get the select box
		auto it = find_if(mBoxes.begin(), mBoxes.end(), [&button](const Box& x) {
			return x.containsCoords(button.x, button.y);
		});

		// if not found, leave
		if(it == mBoxes.end()) {
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
				auto selectedBox = find_if(mBoxes.begin(), mBoxes.end(), [&](const Box& x) {
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

	void PlayState::drawBoxes(Renderer& renderer)
	{
		auto* texture = TextureManager::Instance()->get(mTilesImg);
		for(const auto& x: mBoxes) {
			// only render texture if its solved or selected
			if (x.solved || x.selected) {
				renderer.drawTexture(texture,
									 &x.textureRect, &x.windowRect);
			} else {
				renderer.drawRect(DEFAULT_BOX_COLOR, &x.windowRect);
			}
		}
	}
}
