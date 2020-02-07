// Agent.h

#ifndef AGENT_H_INCLUDED
#define AGENT_H_INCLUDED

#include "FSM.h"
#include "State.h"
#include "Vector.h"
#include "Collider.h"
#include "Timer.h"

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
   Vector2 direction_;

   float hunger_;
   float fear_;

   Vector2 danger_;
   Vector2 wall_;
   Vector2* target_;

   Timer senseTimer_;
   Timer decideTimer_;

   AgentState* currentState_;
   std::vector<AgentState*> stateList_;

   Agent(const char* filepath,
         AgentState* startState,
         Vector2 startPos);
   ~Agent();

	void Render(SDL_Renderer* renderer_);
   void Update(float dt);
   void Move(Vector2 newPos);
	void MoveInDirection(Vector2 direction);

   void ChangeState(AgentState* newState);

   void SenseFood(); // Gives you the vector 2 of closest food.
	void Sense();

   void Decide();
};

#endif //!AGENT_H_INCLUDED