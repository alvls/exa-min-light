#include "testFunction.h"

#define _USE_MATH_DEFINES
#include <math.h>

double func(const double *y, int N)
{
  double f;
  int i;

  f =10*N;
  for(i=0 ; i < N; ++i)
  {
  //f += ((y[i]-(N-i)/(double)N)*(y[i]-(N-i)/(double)N) - 10 * cos(2 * M_PI * (y[i]-(N-i)/(double)N)));
  f += ((y[i])*(y[i]) - 10 * cos(2 * M_PI * (y[i])));
  }

  return f;
}

double function(const double *y)
{
  double res;// = (y[0]-0.1)*(y[0]-0.1)+0.1;

  res = func(y, 3);

  return res;
}