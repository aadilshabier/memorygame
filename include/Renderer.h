#pragma once

#include <vector>

#include "SDL.h"
#include "Square.h"

namespace MemoryGame
{
	using std::vector;

	constexpr int BOX_SIZE = 100;
	constexpr int BORDER_SIZE = 20;

	constexpr SDL_Color BG_COLOR = {0, 0, 0, 255}; // black
	constexpr SDL_Color BOX_COLOR = {255, 255, 255, 255}; // white

	class Renderer
	{
	public:
		/* Create window and renderer with given parameters */
		void init(const char* title, int w, int h);

		~Renderer();

		/* Clear the screen */
		void clear();

		/* Update screen to reflect changes */
		void present();

		SDL_Renderer* getRenderer() { return mRenderer; }
	private:
		SDL_Window *mWindow;
		SDL_Renderer *mRenderer;
	};
}
