//TIMER_H_INCLUDED
#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED
#include "DeltaTime.h"
#include <iostream>

struct Timer
{
   DeltaTime deltaTime_;
   float initialValue_;
   float currentValue_;

   Timer(float time) { // Expects time as seconds
      initialValue_ = time;
      currentValue_ = time;
      deltaTime_.Update(); // I do this to makesure that the actually used dt values are accurate
   }

   bool IsDone() {
      currentValue_ -= deltaTime_.AsSeconds();
      if (currentValue_ <= 0)
      {
         return true;
      }
      return false;
   }
   void Reset() { currentValue_ = initialValue_; }
};

#endif // !TIMER_H_INCLUDED
