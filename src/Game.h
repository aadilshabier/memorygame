#pragma once

#include <cstdint>

#include "Renderer.h"
#include "GameStateMachine.h"

namespace MemoryGame
{
	constexpr uint64_t FPS = 30;
	//Framerate in milliseconds
	constexpr uint64_t FRAMERATE_MS = 1000 / FPS;

	class Game
	{
	public:
		/* Public instance function */
		static Game* Instance();
		/* Run the game */
		void run();
		/* Get the state machine */
		GameStateMachine* getStateMachine() { return &mGameStateMachine; }
		/* Getter and Setter for mRunning */
		bool isRunning() const { return mRunning; }
		void setRunning(bool r) { mRunning = r; }
	private:
		Game();
	private:
		bool mRunning;
		Renderer mRenderer;
		GameStateMachine mGameStateMachine;
	};
}
