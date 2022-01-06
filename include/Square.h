#pragma once

#include "SDL.h"

namespace MemoryGame
{
	class Square
	{
	public:
		Square(int x_, int y_, int w_, int h_, int number_);
		/* check if it contains given coordinates coordinates */
		bool containsCoords(int x, int y);

	public:
		/* Class members */
		SDL_Rect rect;
		int number;
	};
}
