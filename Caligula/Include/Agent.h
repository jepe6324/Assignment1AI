// Agent.h

#ifndef AGENT_H_INCLUDED
#define AGENT_H_INCLUDED

#include "FSM.h"
#include "State.h"
#include "Vector.h"
#include "Collider.h"

struct Sprite;
struct DeltaTime;
struct SDL_Renderer;
struct Grid;

struct Agent : FSM
{
   enum Species {
      WOLF,
      SHEEP
   };

   Sprite* sprite_;
   RectangleCollider collider_;
   Vector2 position_;
   Species species_;
   Grid* grid_;
	float detectionRadius_;

   Vector2 danger_;
   Vector2 wall_;
   Vector2* target_;


   AgentState* currentState_;
   std::vector<AgentState*> stateList_;

   Agent(const char* filepath,
         AgentState* startState,
         std::vector<AgentState*> states,
         Vector2 startPos);
   ~Agent();

	void Render(SDL_Renderer* renderer_);
   void Update(float dt);
   void Move(Vector2 newPos);
	void MoveInDirection(Vector2 direction);

   void SenseFood(); // Gives you the vector 2 of closest food.
	void Sense(Vector2 tileToLookAt);
};

#endif //!AGENT_H_INCLUDED