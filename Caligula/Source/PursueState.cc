// PursueState.cc

#include "PursueState.h"
#include "Agent.h"
#include "Grid.h"
#include <iostream>

PursueState::PursueState()
   : eatTimer_(0.3, true)
{
   stateID = "Pursue";
}

void PursueState::Enter()
{
   std::cout << "GRASS DETECTED: BEGINNING DESTROY SEQUENCE" << std::endl; //beep beep i'm a sheep
   if (agent_ == nullptr)
   {
      //Shits fucked yo
   }
}

void PursueState::Act(float dt)
{
   if (agent_->target_ != nullptr)
   {
      //std::cout << agent_->target_->x_ << " " << agent_->target_->y_ << std::endl;
      
      Vector2 direction = (*agent_->target_ - agent_->position_);
      direction.normalize();

      if (distance(agent_->position_, *agent_->target_) <= 0.2f)
      {
         
         agent_->hunger_ -= agent_->grid_->EatGrass(15.0f * dt, *agent_->target_);

         if (agent_->hunger_ < 0)
         {
            agent_->hunger_ = 0;
            agent_->Sense();
            agent_->Decide();
            return;
         }

         int targetIndex = agent_->grid_->GetTileIndex(agent_->target_->x_, agent_->target_->y_);
         if (agent_->grid_->tiles_.at(targetIndex)->grass_->health_ > 14.8f)
         {
            agent_->target_ = nullptr;
            agent_->grid_->tiles_.at(targetIndex)->grass_->currentState_ == GrassState::DEAD;
         }

      }
      else{
         agent_->MoveInDirection(direction * dt);
      }
   }
}

void PursueState::Exit()
{
}
