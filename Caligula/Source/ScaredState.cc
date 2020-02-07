#include "ScaredState.h"
#include "Agent.h"
#include <iostream>

ScaredState::ScaredState()
{
}

void ScaredState::Enter()
{
	std::cout << "scared" << std::endl;
	direction_ = agent_->direction_ + agent_->danger_;
	//agent_->danger_.Normalize();
	
	//&agent_direction_ = direction_ + agent_->danger_;
}

void ScaredState::Act(float dt)
{
	int yeet = 0;
	agent_->direction_ = Lerp(agent_->direction_, agent_->danger_, dt * 5);
	agent_->direction_.Normalize();
	agent_->MoveInDirection(agent_->direction_ * dt);
}

void ScaredState::Exit()
{
	agent_->danger_ = Vector2(0, 0);
}
