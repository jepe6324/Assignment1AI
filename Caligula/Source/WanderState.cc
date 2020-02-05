//WANDERSTATE.CC
#include "WanderState.h"
#include "Agent.h"
#include <iostream>
#include "Random.h"

WanderState::WanderState()
{
   direction_.x_ = 0;
   direction_.y_ = 0;
}

void WanderState::Enter()
{
   float i, j;
   i = Random::Randf(-1, 1);
   j = Random::Randf(-1, 1);
   direction_.x_ = i;
   direction_.y_ = j;
   direction_.normalize();
	//get position of agent
	//get a direction
}
void WanderState::Exit()
{
	//switch state?
}

void WanderState::Act(float dt)
{
   agent_->MoveInDirection(direction_ * dt);
}
