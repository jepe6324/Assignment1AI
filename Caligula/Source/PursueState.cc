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
      direction.Normalize();

      if (Distance(agent_->position_, *agent_->target_) <= 0.2f)
      {
         
         agent_->hunger_ -= agent_->grid_->EatGrass(15.0f * dt, *agent_->target_);// Sheep specific

         int targetIndex = agent_->grid_->GetTileIndex(*agent_->target_);
         if (agent_->grid_->tiles_.at(targetIndex)->grass_ == nullptr)
         {
            return;
         }
         if (agent_->grid_->tiles_.at(targetIndex)->grass_->health_ > 14.8f)
         {
            agent_->target_ = nullptr;
            agent_->grid_->tiles_.at(targetIndex)->grass_->currentState_ == GrassState::DEAD;
         } // !Sheep specific

      }
      else{
         agent_->direction_ = Lerp(agent_->direction_, direction, dt * 5);
         agent_->direction_.Normalize();
         agent_->MoveInDirection(agent_->direction_ * dt);
      }
   }
}

void PursueState::Exit()
{
}
