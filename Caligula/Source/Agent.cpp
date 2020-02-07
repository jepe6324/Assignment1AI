// Agent.cpp

#include "Agent.h"
#include "Sprite.h"
#include "Service.h"
#include "Spritehandler.h"
#include "Config.h"
#include "DeltaTime.h"
#include "Grid.h"
#include "Random.h"

#include "WanderState.h"
#include "PursueState.h"
#include "BreedState.h"
#include "ScaredState.h"

Agent::Agent(const char* filepath,
             AgentState* startState,
             Vector2 startPos)
   : collider_(startPos.x_, startPos.y_,30,20)
   , decideTimer_(0.2f)
   , senseTimer_(0.4f)
   , hunger_(2)
   , fear_(0)
{
   float i, j;
   i = Random::Randf(-1, 1);
   j = Random::Randf(-1, 1);
   direction_.x_ = i;
   direction_.y_ = j;
   direction_.Normalize();

   sprite_ = Service<SpriteHandler>::Get()->CreateSprite(filepath, 0, 0, 20, 30);
   currentState_ = nullptr;
   ChangeState(startState);
   position_ = startPos;
	detectionRadius_ = 3;
   target_ = nullptr;
}

Agent::~Agent()
{
}

void Agent::Render(SDL_Renderer* renderer_)
{
	SDL_Rect dst = collider_.GetBounds(); //{ position_. , bounds_.y + health_, currentSprite_->GetArea().w - (health_ * 2), currentSprite_->GetArea().h - (health_ * 2) };
	SDL_RenderCopy(renderer_, sprite_->GetTexture(), &sprite_->GetArea(), &dst);

	SDL_SetRenderDrawColor(renderer_, currentState_->color_.r, currentState_->color_.g, currentState_->color_.b, 255);
	if(Config::DEBUGRENDER == TRUE)
		SDL_RenderDrawRect(renderer_, &collider_.GetBounds());
}

void Agent::Update(float dt) // As milliseconds
{
   if (currentState_ != nullptr){
      currentState_->Act(dt);
   }

   if (senseTimer_.IsDone())
   {
      Sense();
      senseTimer_.Reset();
   }

   if (decideTimer_.IsDone())
   {
      Decide();
      decideTimer_.Reset();
   }

   collider_.SetPosition(position_.x_ * Config::TILE_SIZE, position_.y_ * Config::TILE_SIZE);
   if (hunger_ < 15) // Max hunger is 15
      hunger_ += dt;
   if (fear_ > 0.0f) 
      fear_ -= 7.5f * dt;
}

void Agent::Move(Vector2 newPos) {
   // These lines should be used when moving the agents
   Vector2 oldPos = position_;

   int index = grid_->GetTileIndex(oldPos);
   grid_->tiles_.at(index)->agents_[0] = nullptr;

   if (grid_->GetTileIndex(newPos) != -1)
   {
      position_ = newPos;
   }

   index = grid_->GetTileIndex(position_);
   grid_->tiles_.at(index)->agents_[0] = this;
}

void Agent::MoveInDirection(Vector2 direction)
{
	Vector2 newPos = position_ + direction;
	Move(newPos);
}

void Agent::ChangeState(AgentState* newState)
{
   if (currentState_ != nullptr)
   {
      currentState_->Exit();
      delete currentState_;
      currentState_ = nullptr;
   }

   currentState_ = newState;
   currentState_->agent_ = this;
   currentState_->Enter();
}

void Agent::SenseFood()
{
   switch (species_){
	case WOLF:
      target_ = grid_->SenseSheep(position_, detectionRadius_);
      break;
   case SHEEP:
      target_ = grid_->SenseGrass(position_, detectionRadius_);
      break;
   }
}

void Agent::SenseWall()
{
   wall_ = grid_->SenseWall(position_, detectionRadius_);
	//direction_ = direction_;
}

void Agent::SenseDanger()
{
	danger_ = grid_->SenseWolves(position_, detectionRadius_);
	if (danger_.x_ != 0 && danger_.y_ != 0)
	{
		fear_ = 15;
	}
}

void Agent::Sense()
{
   SenseFood();
	if(species_ == Agent::SHEEP)
		SenseDanger();
   SenseWall();
}

float Agent::Die()
{
   float returnValue = 15 - hunger_;
   hunger_ = 15;
   return returnValue;
}

void Agent::Decide()
{
   const char* prevState = currentState_->stateID;

   //std::cout << hunger_ << std::endl;

   if (fear_ > 1.0f && fear_ > hunger_ * 0.7f)
   {
		ChangeState(new ScaredState());
   }
   else if ((hunger_ > 10 && target_ != nullptr)
            || (prevState == "Pursue" && hunger_ > 0.2f && target_ != nullptr))
   {
      ChangeState(new PursueState());
      //Be hungry and eat
   }
   else if (hunger_ < 2 && fear_ < 2)
   {
      ChangeState(new BreedState());
   }
   else
   {
      ChangeState(new WanderState());
   }
   if (currentState_ == nullptr) // for some reason it wont go into the first else statement every time.
   {
      ChangeState(new WanderState());
   }
}