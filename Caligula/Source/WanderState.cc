//WANDERSTATE.CC
#include "WanderState.h"
#include "Agent.h"

WanderState::WanderState():
	decideTimer_(1)
{
}

void WanderState::Enter()
{
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
		int i, j;
		i = -1 + (rand() % (1 - -1 + 1));
		j = -1 + (rand() % (1 - -1 + 1));
		direction_.x_ = i;
		direction_.y_ = j;
		decideTimer_.Reset();
	}
}

void WanderState::Act(float dt)
{
   agent_->MoveInDirection(direction_ * dt);
}
