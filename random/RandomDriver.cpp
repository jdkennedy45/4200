#include "Random.h"
using CSC2110::Random;

#include <iostream>
using namespace std;

int main()
{
   Random* rand = new Random();
   for (int i = 1; i <= 100; i++)
   {
      //int num = rand->getRandomInt(1, 1000);
      float num = rand->getRandomFloat(1, 3);
      cout << num << endl;
   }

   delete rand;
}