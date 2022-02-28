#include <iostream>

#include "Renderer.h"
#include "SDL.h"

namespace MemoryGame
{
	using std::cerr;

	void Renderer::init(const char* title, int w, int h)
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			cerr << "ERROR: Could not initialize SDL: " << SDL_GetError() << '\n';
			exit(1);
		}

		mWindow = SDL_CreateWindow(title,
								   SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
								   w, h,
								   SDL_WINDOW_SHOWN);
		if (mWindow == NULL) {
			cerr << "ERROR: Could not initialize window: " << SDL_GetError() << '\n';
			exit(1);
		}

		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
		if (mRenderer == NULL) {
			cerr << "ERROR: Could not initialize hardware renderer: " << SDL_GetError() << '\n';
			cerr << "Trying to switch to fallback software renderer\n";
			mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_SOFTWARE);
			if (mRenderer == NULL) {
				cerr << "ERROR: Could not initialize software renderer: " << SDL_GetError() << '\n';
				exit(1);
			}
		}
	}

	Renderer::~Renderer()
	{
		SDL_DestroyWindow(mWindow);
		SDL_DestroyRenderer(mRenderer);
		SDL_Quit();
	}

	void Renderer::clear()
	{
		SDL_SetRenderDrawColor(mRenderer, BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a);
		SDL_RenderClear(mRenderer);
	}

	void Renderer::present()
	{
		SDL_RenderPresent(mRenderer);
	}

	void Renderer::drawRect(const SDL_Rect* rect, SDL_Color color)
	{
		SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(mRenderer, rect);
	}
}
