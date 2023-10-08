#pragma once

#include "SDL.h"

namespace MemoryGame
{
	class Box
	{
	public:
	    Box(SDL_Rect _windowRect, SDL_Rect _textureRect, int _number);
		/* check if it contains given coordinates coordinates */
		bool containsCoords(int x, int y) const;

	public:
		/* Class members */
		SDL_Rect windowRect, textureRect;
		int number;
		bool selected = false;
		bool solved = false;
	};
}
