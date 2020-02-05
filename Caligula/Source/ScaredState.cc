#include "ScaredState.h"
#include "Agent.h"
#include <iostream>

ScaredState::ScaredState()
{
	weight_ * 2;
}

void ScaredState::Enter()
{
	std::cout << "SCARED SHEEP!" << std::endl;
	direction_ = agent_->danger_;
	wall_ = agent_->wall_;
	if (wall_ != Vector2(0, 0))
	{
		direction_ = direction_ + (wall_ * weight_);
	}
	direction_ = direction_ * -1;
	direction_.normalize();
}

void ScaredState::Act(float dt)
{
	agent_->MoveInDirection(direction_ * dt);
}

void ScaredState::Exit()
{
}
