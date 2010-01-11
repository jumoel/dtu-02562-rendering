#include "mathfuncs.h"

#include <cstdlib>
#include "Common/CommonDefs.h"

float rand01()
{
  return rand0N(1);
}

float rand02() {
  return rand0N(2);
}

float rand0N(int n) {
  return n*rand()/static_cast<float>(RAND_MAX);
}