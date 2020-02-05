//WANDERSTATE_H_INCLUDED
#ifndef WANDERSTATE_H_INCLUDED
#define WANDERSTATE_H_INCLUDED

#include "State.h"
#include "Vector.h"
#include "Timer.h"

struct Agent;

struct WanderState : AgentState 
{
	std::vector<State*> subStates_;
	State* nextState;
	Vector2 direction_;
	Timer decideTimer_;

	WanderState();

	void Enter();
	bool Update();
	void Exit();

   void Decide(float dt);
   void Act(float dt);
};

#endif // !WANDERSTATE_H_INCLUDED
