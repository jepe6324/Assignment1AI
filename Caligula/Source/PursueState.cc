// PursueState.cc

#include "PursueState.h"
#include "Agent.h"
#include "Grid.h"
#include <iostream>

PursueState::PursueState()
   : eatTimer_(0.3, true)
{
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
      
      Vector2 direction = (*agent_->target_ - agent_->position_);
      direction.normalize();

      if (distance(agent_->position_, *agent_->target_) <= 0.2f)
      {
         
         agent_->hunger_ -= agent_->grid_->EatGrass(2.0f * dt, *agent_->target_);
         if (agent_->hunger_ < 0)
         {
            agent_->hunger_ = 0;
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
