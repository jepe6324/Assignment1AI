//WANDERSTATE.CC
#include "WanderState.h"
#include "Agent.h"
#include <iostream>
#include "Random.h"

WanderState::WanderState()
{
}

void WanderState::Enter()
{
   direction_.x_ = Random::Randf(-1, 1);
   direction_.y_ = Random::Randf(-1, 1);
   direction_.Normalize();
	//get position of agent
	//get a direction
}
void WanderState::Exit()
{
	//switch state?
}

void WanderState::Act(float dt)
{
   agent_->direction_ = Lerp(agent_->direction_, direction_, dt);
   agent_->direction_.Normalize();
   agent_->MoveInDirection(agent_->direction_ * dt);
}
