//WANDERSTATE_H_INCLUDED
#ifndef WANDERSTATE_H_INCLUDED
#define WANDERSTATE_H_INCLUDED

#include "State.h"
#include "Vector.h"

struct WanderState : State 
{
	std::vector<State*> subStates_;
	State* nextState;
	Vector2 direction_;

	void Enter();
	bool Update();
	void Exit();
};

#endif // !WANDERSTATE_H_INCLUDED
