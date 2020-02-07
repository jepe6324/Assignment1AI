#include "BreedState.h"
#include "Agent.h"
#include "Grid.h"
#include "WanderState.h"
#include <iostream>

BreedState::BreedState()
	: BreedTimer_(3)
{
   hungerDecrease_ = 7.5f;
}

void BreedState::Enter()
{
   std::cout << "Breeding" << std::endl;
}

void BreedState::Act(float dt)
{
	if (BreedTimer_.IsDone() && BreedTimer_.paused_ != false)
	{
		agent_->grid_->Breed(agent_->position_, agent_->species_);
		agent_->hunger_ += hungerDecrease_;
		BreedTimer_.paused_ = true;

      agent_->ChangeState(new WanderState());
	}
}

void BreedState::Exit()
{
	agent_->Sense();
	agent_->Decide();
}
