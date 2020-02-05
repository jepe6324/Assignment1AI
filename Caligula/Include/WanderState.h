//WANDERSTATE_H_INCLUDED
#ifndef WANDERSTATE_H_INCLUDED
#define WANDERSTATE_H_INCLUDED

#include "State.h"
#include "Vector.h"

struct Agent;

struct WanderState : AgentState 
{
	Vector2 direction_;

	WanderState();

	void Enter();
   void Act(float dt);
	void Exit();

};

#endif // !WANDERSTATE_H_INCLUDED
