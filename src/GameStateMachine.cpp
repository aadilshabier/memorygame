#include "GameStateMachine.h"

namespace MemoryGame
{
	using std::vector;

	GameStateMachine::GameStateMachine()
		: mGameStates()
	{}

	void GameStateMachine::pushState(GameState* state)
	{
		mGameStates.push_back(state);
		mGameStates.back()->onEnter();
	}

	void GameStateMachine::popState()
	{
		if(!mGameStates.empty()) {
			mGameStates.back()->onExit();
			delete mGameStates.back();
			mGameStates.pop_back();
		}
	}
	void GameStateMachine::changeState(GameState* state)
	{
		if(!mGameStates.empty()) {
			if(mGameStates.back()->getStateType() == state->getStateType()) {
				delete state;
				return;
			}

			mGameStates.back()->onExit();
			delete mGameStates.back();
			mGameStates.pop_back();
		}

		pushState(state);
	}

	void GameStateMachine::update()
	{
		if (!mGameStates.empty())
			mGameStates.back()->update();
	}
	void GameStateMachine::render(Renderer& renderer)
	{
		if (!mGameStates.empty())
			mGameStates.back()->render(renderer);
	}
}
