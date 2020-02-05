//SCAREDSTATE_H_INCLUDED
#ifndef SCAREDSTATE_H_INCLUDED
#define SCAREDSTATE_H_INCLUDED


#include "State.h"
#include "Vector.h"

struct Agent;

struct ScaredState : AgentState
{
	Vector2 direction_;
	Vector2 wall_;
	float weight_;

	ScaredState();

	void Enter();
	void Act(float dt);
	void Exit();

};

#endif // !SCAREDSTATE_H_INCLUDED