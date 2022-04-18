#pragma once

#include "SDL.h"

namespace MemoryGame
{
	class Box
	{
	public:
		Box(int _x, int _y, int _w, int _h, int _number, SDL_Color _color);
		/* check if it contains given coordinates coordinates */
		bool containsCoords(int x, int y) const;

	public:
		/* Class members */
		SDL_Rect rect;
		int number;
		SDL_Color color;
		bool selected, solved;
	};
}
