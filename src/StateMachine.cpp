#include "StateMachine.h"

StateMachine::StateMachine(State* startingState) {
	States.push(startingState);
}

StateMachine::StateMachine() {
	//do nothing
}

void StateMachine::popState() {
	if (States.top() != NULL) { //nullptr
		State* pointer = States.top();
		States.pop();
		delete pointer;
	}
}

void StateMachine::popState(unsigned times) {
	for (int i=0 ; i<times ; i++) {
        if (States.top() != NULL) { //nullptr
            State* pointer = States.top();
            States.pop();
            delete pointer;
        }
	}
}

void StateMachine::pushState(State* newState) {
	States.push(newState);
}

void StateMachine::replaceState(State* newState) {
	this->popState();
	States.push(newState);
}

int StateMachine::numberOfStates() {
    return States.size();
}

State* StateMachine::topState() {
	return States.top();
}
