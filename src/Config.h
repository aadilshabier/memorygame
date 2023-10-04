#pragma once

namespace MemoryGame {
	// dimensions of window
	static constexpr int W = 740;
	static constexpr int H = 620;

	constexpr uint64_t FPS = 30;
	//Framerate in milliseconds
	constexpr uint64_t FRAMERATE_MS = 1000 / FPS;

	// Number of boxes in X and Y dims
	static constexpr int X = 6;
	static constexpr int Y = 5;
}
