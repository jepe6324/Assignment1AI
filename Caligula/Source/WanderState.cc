//WANDERSTATE.CC
#include "WanderState.h"
#include "Agent.h"
#include <iostream>

WanderState::WanderState():
	decideTimer_(1)
{
}

void WanderState::Enter()
{
   float i, j;
   i = float(rand()) / float(RAND_MAX);
   j = float(rand()) / float(RAND_MAX);
   direction_.x_ = i;
   direction_.y_ = j;
   direction_.normalize();
	//get position of agent
	//get a direction
}
bool WanderState::Update()
{
	//move in that direction
	return true;
}
void WanderState::Exit()
{
	//switch state?
}

void WanderState::Sense(float dt)
{
}

void WanderState::Decide(float dt)
{
	if (decideTimer_.IsDone())
	{
      float i, j;
      i = float(rand()) / float(RAND_MAX);
      j = float(rand()) / float(RAND_MAX);
      direction_.x_ = i;
      direction_.y_ = j;

      direction_.normalize();
		decideTimer_.Reset();
	}
}

void WanderState::Act(float dt)
{
   agent_->MoveInDirection(direction_ * dt);
}
