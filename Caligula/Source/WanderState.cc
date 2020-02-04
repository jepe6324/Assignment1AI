//WANDERSTATE.CC
#include "WanderState.h"
#include "Agent.h"

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

}

void WanderState::Act(float dt)
{
   agent_->Move(Vector2(1, 2));
}
