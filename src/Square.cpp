#include "Square.h"

namespace MemoryGame
{
	Square::Square(int x_, int y_, int w_, int h_, int number_)
		: rect{x_, y_, w_, h_}
		, number(number_)
	{
	}

	bool Square::containsCoords(int x, int y)
	{
		const auto& rect = this->rect;
		return (rect.x <= x && rect.y <= y &&
				x < (rect.x+rect.w) && y < (rect.y+rect.h));
	}
}
