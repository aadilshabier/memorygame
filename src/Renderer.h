#pragma once

#include <vector>

#include "SDL.h"
#include "Box.h"

namespace MemoryGame
{
	using std::vector;

	constexpr int BOX_SIZE = 100;
	constexpr int BORDER_SIZE = 20;

	constexpr SDL_Color BG_COLOR = {0, 0, 0, 255}; // black
	constexpr SDL_Color DEFAULT_BOX_COLOR = {255, 255, 255, 255}; // white

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

		/* Draw an SDL_Rect with the given color */
		void drawRect(SDL_Color color, const SDL_Rect* rect);

		/* Draw an SDL_Texture with the given src and dest SDL_Rect's */
		void drawTexture(SDL_Texture* texture,
						 const SDL_Rect* srcrect, const SDL_Rect* dstrect);
	public:
		SDL_Renderer *mRenderer;
	private:
		SDL_Window *mWindow;
	};
}
