// Agent.cpp

#include "Agent.h"
#include "Sprite.h"
#include "Service.h"
#include "Spritehandler.h"
#include "Config.h"
#include "DeltaTime.h"

Agent::Agent(const char* filepath,
             AgentState* startState,
             std::vector<AgentState*> states,
             Vector2 startPos)
   : collider_(startPos.x_, startPos.y_,30,20)
{
   sprite_ = Service<SpriteHandler>::Get()->CreateSprite(filepath, 0, 0, 20, 30);
   currentState_ = startState;
   stateList_ = states;
   position_ = startPos;
}

Agent::~Agent()
{
}

void Agent::Render(SDL_Renderer* renderer_)
{
	SDL_Rect dst = collider_.GetBounds(); //{ position_. , bounds_.y + health_, currentSprite_->GetArea().w - (health_ * 2), currentSprite_->GetArea().h - (health_ * 2) };
	SDL_RenderCopy(renderer_, sprite_->GetTexture(), &sprite_->GetArea(), &dst);

	SDL_SetRenderDrawColor(renderer_, 0, 150, 255, 0);
	if(Config::DEBUGRENDER == TRUE)
		SDL_RenderDrawRect(renderer_, &collider_.GetBounds());
}

void Agent::Update(DeltaTime dt) // As milliseconds
{
   currentState_->Sense(); // add interval
   currentState_->Decide(); // add interval
   currentState_->Act();
}