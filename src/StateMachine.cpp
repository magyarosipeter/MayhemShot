#include "StateMachine.h"

StateMachine::StateMachine(State* startingState) {
	States.push(startingState);
}

StateMachine::StateMachine() {
	//do nothing
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

int StateMachine::numberOfStates() {
    return States.size();
}

State* StateMachine::topState() {
	return States.top();
}
