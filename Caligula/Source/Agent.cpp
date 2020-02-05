// Agent.cpp

#include "Agent.h"
#include "Sprite.h"
#include "Service.h"
#include "Spritehandler.h"
#include "Config.h"
#include "DeltaTime.h"
#include "Grid.h"

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

	SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 0);
	if(Config::DEBUGRENDER == TRUE)
		SDL_RenderDrawRect(renderer_, &collider_.GetBounds());
}

void Agent::Update(float dt) // As milliseconds
{
   if (currentState_ != nullptr){
      currentState_->Decide(dt); // add interval
      currentState_->Act(dt);
   }

   collider_.SetPosition(position_.x_ * Config::TILE_SIZE, position_.y_ * Config::TILE_SIZE);
}

void Agent::Move(Vector2 newPos) {
   // These lines should be used when moving the agents
   Vector2 oldPos = position_;

   int index = grid_->GetTileIndex(oldPos.x_, oldPos.y_);
   grid_->Tiles_.at(index)->agents_[0] = nullptr;

   if (grid_->GetTileIndex(newPos.x_, newPos.y_) != -1)
   {
      position_ = newPos;
   }

   index = grid_->GetTileIndex(position_.x_, position_.y_);
   grid_->Tiles_.at(index)->agents_[0] = this;
}

void Agent::MoveInDirection(Vector2 direction)
{
	Vector2 newPos = position_ + direction;
	Move(newPos);
}

void Agent::SenseFood()

{
   switch (species_)
	case WOLF:
      target_ = grid_->SenseSheep(position_, detectionRadius_);
      break;
   case SHEEP :
      target_ = grid_->SenseGrass(position_, detectionRadius_);
      break;
}
