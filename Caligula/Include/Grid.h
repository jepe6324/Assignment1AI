//GRID_H_INCLUDED

#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include "Tile.h"
#include "Grass.h"
#include <vector>

struct Grass; // NOTE: For some reason it suddenly requires forward declarations
struct Tile;  // Ask Jerry for help

struct Grid {
	void Create();
	void Render(SDL_Renderer* renderer_);
   
   bool Spread(int x, int y);

   int GetTileIndex(int x, int y);

	std::vector<Tile*> Tiles_;
   std::vector<Grass*> *grass_;
};

#endif // !GRID_H_INCLUDED
