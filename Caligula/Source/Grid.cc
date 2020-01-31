//Grid.cc
#include "Grid.h"
#include "Config.h"
#include <iostream>

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
			Tiles_.push_back(tmp);
			posX += difference;
		}
		posY += difference;
		posX = 0;
	}
};

void Grid::Render(SDL_Renderer* renderer_) {
	for (Tile* tile : Tiles_)
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
         tmp->x_ = x;
         tmp->y_ = y;
         tmp->grid_ = this;
         Tiles_.at(GetTileIndex(x,y))->grass_ = tmp;
         grass_->push_back(tmp);

         return true;
      }
   }
   return false;
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

const char* Grid::LookAtTile(int x, int y)
{
   int index = GetTileIndex(x, y);
   if (index == -1)
   {
      return "cbt";
   }
   return LookAtTile(index);
}

const char* Grid::LookAtTile(int index)
{
   if (index > Tiles_.size()){
      return "cbt";
   }

   if (Tiles_.at(index)->agents_[1] != nullptr) { // looks at the wolf
      return "Wolf";
   }
   else if (Tiles_.at(index)->agents_[0] != nullptr) { // looks at the sheep
      return "Sheep";
   }
   else if (Tiles_.at(index)->grass_ != nullptr) { // Looks at the grass
      return "Grass";
   }
   else {
      return "Empty";
   }
}
