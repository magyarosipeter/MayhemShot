#include "StateMachine.h"

StateMachine::StateMachine(State* startingState) {
	States.push(startingState);
}

void StateMachine::popState() {
	if (States.top() != NULL) { //nullptr
		States.pop();
	}
}

void StateMachine::pushState(State* newState) {
	States.push(newState);
}

void StateMachine::replaceState(State* newState) {
	if (States.top() != NULL) { //nullptr
		States.pop();
	}
	States.push(newState);
}

State* StateMachine::topState() {
	return States.top();
}
