#if !defined RANDOM
#define RANDOM

#include "randomc.h"

namespace CSC1310
{
class Random
{
   private:
      CRandomMother rand_mother;
	  Random();
	  
   public:
      static Random* getRandom();
      virtual ~Random();
	  
      int getRandomInt(int lower, int upper);
      float getRandomFloat(float lower, float upper); 
};
}

#endif
