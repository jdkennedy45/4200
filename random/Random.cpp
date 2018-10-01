#include "Random.h"
using CSC1310::Random;

#include <ctime>
#include <cstdlib>

Random::Random() : rand_mother(time(NULL))
{}

Random::~Random()
{}

Random* Random::getRandom()
{
	static Random random;
	return &random;
}

int Random::getRandomInt(int lower, int upper)
{
   return rand_mother.IRandom(lower, upper);
}

float Random::getRandomFloat(float lower, float upper)
{
   float random_float = (float) rand_mother.Random();
   random_float = lower + random_float*(upper - lower);
   return random_float;
}
