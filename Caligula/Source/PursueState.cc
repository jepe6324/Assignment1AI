// PursueState.cc

#include "PursueState.h"
#include "Agent.h"
#include "Grid.h"
#include "WanderState.h"
#include <iostream>

PursueState::PursueState()
   : eatTimer_(0.3, true)
{
   stateID = "Pursue";
}

void PursueState::Enter()
{
   color_ = { 0,255,0,0 };
}

void PursueState::Act(float dt)
{
   if (agent_->target_ != nullptr)
   {
      Vector2 direction = (*agent_->target_ - agent_->position_);

      if (Distance(agent_->position_, *agent_->target_) <= 0.4f)
      {
         int targetIndex = agent_->grid_->GetTileIndex(*agent_->target_);

         switch (agent_->species_){
         case Agent::SHEEP:
            agent_->hunger_ -= agent_->grid_->EatGrass(15.0f * dt, *agent_->target_);// Sheep specific
            if (agent_->grid_->tiles_.at(targetIndex)->grass_ == nullptr)
            {
               agent_->target_ == nullptr;
               return agent_->ChangeState(new WanderState());
            }
            if (agent_->grid_->tiles_.at(targetIndex)->grass_->health_ > 14.8f)
            {
               agent_->target_ = nullptr;
               agent_->grid_->tiles_.at(targetIndex)->grass_->currentState_ == GrassState::DEAD;
            } // !Sheep specific
            break;
         case Agent::WOLF:
            agent_->hunger_ -= agent_->grid_->tiles_.at(targetIndex)->agents_[0]->Die();
            break;
         }
      }
      else{
         agent_->direction_ = Lerp(agent_->direction_, direction, dt * 5);
         agent_->direction_.Normalize();
         agent_->MoveInDirection(agent_->direction_ * (agent_->speed_ * dt));
      }
   }
}

void PursueState::Exit()
{
}
