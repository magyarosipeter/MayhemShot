#pragma once

#include <stack>

#include "MoreInfo.h"
#include "State.h"

class State;

class StateMachine {

public:
	StateMachine(State* startingState);
	StateMachine();

	void popState();
	void pushState(State* newState);
	void replaceState(State* newState);

	int numberOfStates();

	State* topState();

private:
	std::stack<State*> States;
};
