// Agent.cpp

#include "Agent.h"
#include "Sprite.h"
#include "Service.h"
#include "Spritehandler.h"
#include "DeltaTime.h"

Agent::Agent(const char* filepath,
             AgentState* startState,
             std::vector<AgentState*> states,
             Vector2 startPos)
   : collider_(0,0,0,0)
{
   sprite_ = Service<SpriteHandler>::Get()->CreateSprite(filepath, 0, 0, 20, 30);
   currentState_ = startState;
   stateList_ = states;
   position_ = startPos;
}

Agent::~Agent()
{
}

void Agent::Update(DeltaTime dt) // As milliseconds
{
   currentState_->Sense(); // add interval
   currentState_->Decide(); // add interval
   currentState_->Act();
}