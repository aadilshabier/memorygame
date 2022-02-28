#include "Box.h"
#include "SDL.h"

#include <iostream>

namespace MemoryGame
{
	Box::Box(int _x, int _y, int _w, int _h, int _number, SDL_Color _color)
		: rect{_x, _y, _w, _h}
		, number(_number)
		, color(_color)
		, selected(false)
		, solved(false)
	{
	}

	bool Box::containsCoords(int x, int y) const
	{
		const auto& rect = this->rect;
		return (rect.x <= x && rect.y <= y &&
				x < (rect.x+rect.w) && y < (rect.y+rect.h));
	}
}
