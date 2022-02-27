#pragma once

#include <vector>

#include "GameState.h"

namespace MemoryGame
{
	using std::vector;

	class GameStateMachine
	{
	public:
		GameStateMachine();
		/* Push a state to the top of the stack */
		void pushState(GameState* state);
		/* Pop a state from the top of the stack if it exists */
		void popState();
		/* Change the state at the top of the stack to the new state if ther GameStateType's are different, if stack is empty, it pushes a state to the stack */
		void changeState(GameState* state);

		/* Update the current GameState */
		void update();
		/* Render the current GameState */
		void render(Renderer& renderer);
	private:
		vector<GameState*> mGameStates;
	};
}
