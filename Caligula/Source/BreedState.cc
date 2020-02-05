#include "BreedState.h"
#include "Agent.h"
#include "Grid.h"

BreedState::BreedState()
	: BreedTimer_(3)
{
}

void BreedState::Enter()
{
}

void BreedState::Act(float dt)
{
	if (BreedTimer_.IsDone() && BreedTimer_.paused_ != false)
	{
		agent_->grid_->Breed(agent_->position_, agent_->species_);
		agent_->hunger_ += hungerDecrease_;
		BreedTimer_.paused_ = true;
	}
}

void BreedState::Exit()
{
	agent_->Sense();
	agent_->Decide();
}
