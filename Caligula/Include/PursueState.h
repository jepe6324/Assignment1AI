// PursueState.h

#ifndef PURSUESTATE_H_INCLUDED
#define PURSUESTATE_H_INCLUDED

#include "State.h"
#include "Vector.h"
#include "Timer.h"

struct Agent;

struct PursueState : AgentState
{
   PursueState();

   Timer eatTimer_;

   void Enter();
   void Act(float dt);
   void Exit();
};

#endif // !PURSUESTATE_H_INCLUDED
