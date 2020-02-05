#include "Random.h"

float Random::Randf(float min, float max)
{ // TODO
   float tmp = float(rand()) / float(RAND_MAX);
   float abs = max - min;
   return (tmp * abs) + min;
}

int Random::Rand(int min, int max)
{ // TODO
   return min + (rand() %(max-min + 1)); // Inclusive?
}