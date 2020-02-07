#include "Grass.h"
#include "Service.h"
#include "SpriteHandler.h"
#include "Config.h"
#include <iostream>

Grass::Grass():
	EatenTimer_(3)
{
	EatenTimer_.Pause();
}

void Grass::Create(const char* p_textureFilePath, int xPos, int yPos)
{
	bounds_.x = xPos;
	bounds_.y = yPos;
	bounds_.h = Config::TILE_SIZE;
	bounds_.w = Config::TILE_SIZE;
	health_ = (rand() % (15+1 - 10)) + 10;
	minHealth_ = 15;
	currentSprite_ = Service<SpriteHandler>::Get()->CreateSprite(p_textureFilePath, 0, 0, bounds_.h, bounds_.w);

	currentState_ = GROWING;
   decideAccumulator = 0;
	maturityAccumulator = 5;
}

void Grass::Render(SDL_Renderer* renderer_) {
	SDL_Rect dst = { bounds_.x + health_, bounds_.y + health_, currentSprite_->GetArea().w - (health_ * 2), currentSprite_->GetArea().h - (health_ * 2) };
	SDL_RenderCopy(renderer_, currentSprite_->GetTexture(), &currentSprite_->GetArea(), &dst);

	SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 0);
	if (Config::DEBUGRENDER == TRUE)
		SDL_RenderDrawRect(renderer_, &bounds_);
}

void Grass::Sense(float dt) {
	if (health_ <= 0)
	{
		maturityAccumulator -= dt;
		if (maturityAccumulator <= 0)
			currentState_ = DYING;
	}

   if (grid_->LookAtTile(position_) != "Grass") // If it senses something other that grass, it's being trampled
   {
      prevState_ = currentState_;
      currentState_ = TRAMPLED;
   }
   else if (currentState_ == TRAMPLED) {
      currentState_ = prevState_;
   }

}

void Grass::Decide(float dt) {

   decideAccumulator += dt;

   if (decideAccumulator > 1){
         switch (currentState_)
      {
      case GROWING:
         if (health_ <= 0)
         {
				health_ = 0;
            currentState_ = SPREADING;
         }
         break;
      case SPREADING:
			tileToSpread = rand() % 4;
         break;
      default:
         break;
      }
      decideAccumulator -= 1;
   }
}

void Grass::Act(float dt) {
	switch (currentState_)
	{
	case GROWING:
      if (health_ >= 0){
         health_ -= float(dt) * (float(rand()) / float(RAND_MAX)) * 10;
      }
		break;
	case TRAMPLED:
		break;
	case SPREADING:
		if (tileToSpread == 0)
			if (grid_->Spread(position_.x_ - 1, position_.y_))
				return;
		if (tileToSpread == 1)
			if (grid_->Spread(position_.x_ + 1, position_.y_))
				return;
		if (tileToSpread == 2)
			if (grid_->Spread(position_.x_, position_.y_ - 1))
				return;
		if (tileToSpread == 3)
			if (grid_->Spread(position_.x_, position_.y_+ 1))
				return;
		break;
	case DYING:
		if (health_ <= minHealth_) {
			health_ += float(dt) * (float(rand()) / float(RAND_MAX)) * 10;
		}
		else
		{
         currentState_ = DEAD;
			//delete grass
		}
		break;
	}
}

float Grass::Eaten(float biteSize)
{
	float remainingHealth = minHealth_ - health_;
	if (biteSize < remainingHealth)
	{
		health_ += biteSize;
		currentState_ = DYING;
		EatenTimer_.Start();
		EatenTimer_.Reset();
		return biteSize;
	}
	else
	{
		health_ += remainingHealth;
		currentState_ = DEAD;
		return remainingHealth;
	}
}
