#include <iostream>
#include <vector>

#include "Renderer.h"
#include "SDL.h"

namespace MemoryGame
{
	using std::cerr;
	using std::vector;

	void Renderer::init(const char* title, int w, int h)
	{
		mWindow = SDL_CreateWindow(title,
								   SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
								   w, h,
								   SDL_WINDOW_SHOWN);
		if (mWindow == NULL) {
			cerr << "ERROR: COuld not initialize window: " << SDL_GetError() << '\n';
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

	void Renderer::drawSquares(const vector<Square>& squares)
	{
		SDL_SetRenderDrawColor(mRenderer, BOX_COLOR.r, BOX_COLOR.g, BOX_COLOR.b, BOX_COLOR.a);
		for(const auto& x: squares)
			SDL_RenderFillRect(mRenderer, &x.rect);
	}

	void Renderer::present()
	{
		SDL_RenderPresent(mRenderer);
	}
}
