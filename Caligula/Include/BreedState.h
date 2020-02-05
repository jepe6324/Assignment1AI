//BREEEDSTATE_H_INCLUDED
#ifndef BREEEDSTATE_H_INCLUDED
#define BREEEDSTATE_H_INCLUDED


#include "State.h"
#include "Vector.h"
#include "Timer.h"

struct Agent;

struct BreedState : AgentState
{
	Timer BreedTimer_;
	float hungerDecrease_;
	BreedState();

	void Enter();
	void Act(float dt);
	void Exit();

};

#endif // !BREEEDSTATE_H_INCLUDED