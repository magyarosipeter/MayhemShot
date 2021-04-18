#pragma once

#include <stack>

#include "MoreInfo.h"
#include "State.h"

class StateMachine {

public:
	StateMachine(State* startingState);

	void popState();
	void pushState(State* newState);
	void replaceState(State* newState);

	State* topState();

private:
	std::stack<State*> States;
};
