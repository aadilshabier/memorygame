#include <iostream>

#include "Renderer.h"
#include "SDL.h"

namespace MemoryGame
{
	using std::cerr;

	void Renderer::init(const char* title, int w, int h)
	{
		mWindow = SDL_CreateWindow(title,
								   SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
								   w, h,
								   SDL_WINDOW_SHOWN);
		if (mWindow == NULL) {
			cerr << "ERROR: Could not initialize window: " << SDL_GetError() << '\n';
			exit(1);
		}

		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
	}

	Renderer::~Renderer()
	{
		SDL_DestroyWindow(mWindow);
		SDL_DestroyRenderer(mRenderer);
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
}
