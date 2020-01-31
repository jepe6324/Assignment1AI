// Agent.cpp

#include "Agent.h"
#include "Sprite.h"
#include "Service.h"
#include "Spritehandler.h"

Agent::Agent(const char* filepath,
             State* startState,
             std::vector<State*> states,
             Vector2 startPos)
   : collider_(0,0,0,0)
{
   sprite_ = Service<SpriteHandler>::Get()->CreateSprite(filepath, 0, 0, 20, 30);
   m_currentState = startState;
   m_states = states;
   position_ = startPos;
}

Agent::~Agent()
{
}
