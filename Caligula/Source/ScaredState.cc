#include "ScaredState.h"
#include "Agent.h"
#include <iostream>

ScaredState::ScaredState()
{
}

void ScaredState::Enter()
{
	//std::cout << "scared" << std::endl;
   direction_ = agent_->direction_;
   if (agent_->danger_.x_ != 0 && agent_->danger_.y_ != 0)
	   direction_ = agent_->danger_;
   direction_.Normalize();

   color_ = { 255,0,0,0 };

   agent_->senseTimer_.currentValue_ = 0.1f;
}

void ScaredState::Act(float dt)
{
	agent_->direction_ = Lerp(agent_->direction_, agent_->wall_ + direction_, dt * 5);
   //agent_->direction_ = agent_->direction_ + agent_->wall_ + direction_;
	agent_->direction_.Normalize();
	agent_->MoveInDirection(agent_->direction_ * agent_->speed_ *  dt);
}

void ScaredState::Exit()
{
   //std::cout << "Is cool" << std::endl;
	//agent_->danger_ = Vector2(0, 0);
}
