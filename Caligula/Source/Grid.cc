//Grid.cc
#include "Grid.h"
#include "Config.h"
#include "WanderState.h"
#include <iostream>

Grid::Grid()
   : grass_(new std::vector<Grass*>())
   , agents_(new std::vector<Agent*>())
{
}

void Grid::Create()
{
	int posX = 0;
	int posY = 0;
	int difference = Config::TILE_SIZE;
	for (int i = 0; i < Config::SCREEN_HEIGHT / Config::TILE_SIZE; i++)
	{
		for (int j = 0; j < Config::SCREEN_WIDTH / Config::TILE_SIZE; j++)
		{
			Tile* tmp = new Tile;
			tmp->Create("../Assets/dirt.png", posX, posY, difference, difference);
			tiles_.push_back(tmp);
			posX += difference;
		}
		posY += difference;
		posX = 0;
	}
};

void Grid::Render(SDL_Renderer* renderer_) {
	for (Tile* tile : tiles_)
	{
		tile->Render(renderer_);
	}
}

bool Grid::Spread(int x, int y) // The grid it wants to spread too
{
   const char * tile = LookAtTile(x, y);
   if (tile == "cbt")
   {
      return false;
   }

   if (rand() % 2 == 0)
   {
      if (tile == "Empty")
      {
         Grass* tmp = new Grass();
         tmp->Create("../Assets/grass.png", x * Config::TILE_SIZE, y * Config::TILE_SIZE);
         tmp->position_.x_ = x;
         tmp->position_.y_ = y;
         tmp->grid_ = this;
         grass_->push_back(tmp);
         tiles_.at(GetTileIndex(x, y))->grass_ = tmp;

         return true;
      }
   }
   return false;
}

bool Grid::Breed(Vector2 pos, Agent::Species species)
{
	const char* tile = LookAtTile(pos);
	if (tile == "cbt") //outside bounds
	{
		return false;
	}
	switch (species)
	{
		case Agent::Species::WOLF:
			if (tile != "Wolf")
			{
				Agent* tmpWolf = new Agent("../Assets/wolf.png", new WanderState(), pos);

				tmpWolf->currentState_->agent_ = tmpWolf;

				tmpWolf->grid_ = this;
				int index = GetTileIndex(pos);
				tiles_[index]->agents_[1] = tmpWolf;
				agents_->push_back(tmpWolf);
				return true;
			}
			break;
		case Agent::Species::SHEEP:
			if (tile != "Sheep")
			{
				Agent* tmpSheep = new Agent("../Assets/sheep.png", new WanderState(), pos);
            tmpSheep->species_ = Agent::SHEEP;

				tmpSheep->grid_ = this;
            tmpSheep->hunger_ = 7.5f; // Hardcoded to half hunger
				int index = GetTileIndex(pos);
				tiles_[index]->agents_[0] = tmpSheep;
				agents_->push_back(tmpSheep);
            
				return true;
			}
			break;
	}
	
	return false;
}

float Grid::EatGrass(float biteSize, Vector2 pos)
{
   int index = GetTileIndex(pos);
   if (tiles_.at(index)->grass_ == nullptr)
   {
      return -1.0f;
   }
   return tiles_.at(index)->grass_->Eaten(biteSize); // Bless you God for this boutiful harvest. Amen.
}

int Grid::GetTileIndex(int x, int y)
{
   int index = 0;

   int maxX = Config::SCREEN_WIDTH  / Config::TILE_SIZE;
   int maxY = Config::SCREEN_HEIGHT / Config::TILE_SIZE;

   if (x < maxX && x >= 0 && y < maxY && y >= 0)
   {
      index = y * (maxX);
      index += x;
   }
   else
      return -1; // Assume -1 error

   return index;
}

int Grid::GetTileIndex(Vector2 pos)
{
   return GetTileIndex(pos.x_, pos.y_);
}

const char* Grid::LookAtTile(int x, int y)
{
   int index = GetTileIndex(x, y);
   if (index == -1)
   {
      return "cbt";
   }
   return LookAtTile(index);
}

const char* Grid::LookAtTile(Vector2 pos)
{
   return LookAtTile(pos.x_, pos.y_);
}

const char* Grid::LookAtTile(int index)
{
   if (index > tiles_.size()){
      return "cbt";
   }
   else if (tiles_.at(index)->agents_[1] != nullptr) { // looks at the wolf
      return "Wolf";
   }
   else if (tiles_.at(index)->agents_[0] != nullptr) { // looks at the sheep
      return "Sheep";
   }
   else if (tiles_.at(index)->grass_ != nullptr) { // Looks at the grass
      return "Grass";
   }
   else {
      return "Empty";
   }
}

Vector2* Grid::SenseSheep(Vector2 pos, float radius)
{
   float distance = 0;
   float closestDst = -1;
   Vector2* result = nullptr;
   Vector2* tmp;
   for (int i = 0; i < agents_->size(); i++)
   {
      tmp = &agents_->at(i)->position_;
      
      if (agents_->at(i)->species_ == Agent::WOLF)
      {
         continue;
      }

      Vector2 distVect = *tmp - pos; // I don't know how to improve operator overloading
      distance = Magnitude(distVect);
      if (distance < closestDst && distance <= radius || closestDst == -1)
      {
         result = tmp;
      }
   }
   return result;
}

Vector2* Grid::SenseGrass(Vector2 pos, float radius)
{
   float distance = 0;
   float closestDst = -1;

   Vector2* result = nullptr;
   Vector2* tmp;
   for (int i = 0; i < grass_->size(); i++)
   {
      tmp = &grass_->at(i)->position_;

      Vector2 distVect = *tmp - pos; // I don't know how to improve operator overloading
      distance = Magnitude(distVect);
      if (distance < closestDst && distance <= radius
          || closestDst == -1 && distance <= radius)
      {
         result = tmp;
         closestDst = distance;
      }
   }
   return result;
}
