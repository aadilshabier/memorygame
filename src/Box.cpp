#include "Box.h"
#include "SDL.h"

#include <iostream>

namespace MemoryGame
{
	Box::Box(SDL_Rect _windowRect, SDL_Rect _textureRect, int _number)
		: windowRect{_windowRect}
		, textureRect{_textureRect}
		, number{_number}
	{
	}

	bool Box::containsCoords(int x, int y) const
	{
		const auto& rect = this->windowRect;
		return (rect.x <= x && rect.y <= y &&
				x < (rect.x+rect.w) && y < (rect.y+rect.h));
	}
}
