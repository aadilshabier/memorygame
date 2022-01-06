#include <iostream>

#include "Game.h"

using namespace MemoryGame;

constexpr int X = 6;
constexpr int Y = 6;

int main()
{
	Game game(X, Y);
	game.run();

	return 0;
}
