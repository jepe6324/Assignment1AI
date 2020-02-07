//GRID_H_INCLUDED

#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include "Tile.h"
#include "Grass.h"
#include "Vector.h"
#include "Agent.h"
#include <vector>

struct Grass; // NOTE: For some reason it suddenly requires forward declarations
struct Tile;  // Ask Jerry for help

struct Grid {
   Grid();

	void Create();
	void Render(SDL_Renderer* renderer_);
   
   bool Spread(int x, int y);
   bool Spread(Vector2 pos);
	bool Breed(Vector2 pos, Agent::Species specie);
   float EatGrass(float biteSize, Vector2 pos);

   int GetTileIndex(int x, int y);
   int GetTileIndex(Vector2 pos);
   Vector2 GetTilePos(int index);
   const char* LookAtTile(int x, int y);
   const char* LookAtTile(Vector2 pos);
   const char* LookAtTile(int index); // the grid has to now if a agent is in a tile
	std::vector<Tile*> tiles_;
   std::vector<Grass*> *grass_;
   std::vector<Agent*> *agents_;

   Vector2* SenseSheep(Vector2 pos, float radius);
   Vector2* SenseGrass(Vector2 pos, float radius);
};

#endif // !GRID_H_INCLUDED
