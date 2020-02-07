#include "BreedState.h"
#include "Agent.h"
#include "Grid.h"
#include "WanderState.h"
#include "Random.h"
#include <iostream>

BreedState::BreedState()
	: BreedTimer_(0)
{
   hungerIncrease_ = 7.5f; // How much energy the sheep uses to breed.
}

void BreedState::Enter()
{
}

void BreedState::Act(float dt)
{
   float success = false;
   for (int i = 0; i < 5; i++)
   {
      Vector2 spawnPos = agent_->position_;
      spawnPos.x_ += Random::Rand(-1, 1);
      spawnPos.y_ += Random::Rand(-1, 1);
      if (agent_->grid_->Breed(spawnPos, agent_->species_))
         break;
   }
   agent_->hunger_ += hungerIncrease_;
   return agent_->ChangeState(new WanderState());
}

void BreedState::Exit()
{
}
