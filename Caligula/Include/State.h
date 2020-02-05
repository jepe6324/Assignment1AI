#pragma once

#include <string>
#include <vector>

struct Agent;

struct State
{
	std::vector<State*> subStates_;
   State* nextState;

	State() {};
	virtual ~State() {};
	
   virtual void Enter() {};
	virtual bool Update() = 0; /*Should return false if state should be changed*/
	virtual void Exit() {};
};

struct AgentState : State
{
   Agent* agent_;
   ~AgentState() {};

   virtual void Decide(float dt) {};
   virtual void Act(float dt) {};
};