#include "method.h"
#include <gtest.h>

#define _USE_MATH_DEFINES
#include <math.h>

// ------------------------------------------------------------------------------------------------
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

class TMethodTest : public ::testing::Test 
{
protected:
  double A[MaxDim];
  double B[MaxDim];
  int NumOfFunc;
  int N;
  TTask* task;
  TSearchData* pData;
  int MaxNumOfTrials;
  double eps;
  double r;
  double reserv;
  int m;
  int L;
  int curl;

  TMethod* method;
  TMethodTest():  method(0)
  {
      NumOfFunc = 1;
      N = 3;
      const tFunction f[MaxNumOfFunc] = {&function};
      task = new TTask(N, N, NumOfFunc, A, B, f);
      pData = new TSearchData(NumOfFunc);
      for(int i = 0; i < MaxDim; i++)
      {
        A[i] = -1.1;
        B[i] = 1.2;
      }
      MaxNumOfTrials = 10000;
      eps = 0.001;
      r = 2.3;
      reserv = 0.001;
      m = 10;
      L = 1;
      curl = 0;
  }

  void CreateMethod() 
  {
    method = new TMethod(MaxNumOfTrials, eps, r, reserv, m, L, curl, task, pData); 
  }

  ~TMethodTest()
  {
    delete task;
    delete pData;
    delete method;
  }
};


/*Проверка входных параметров в конструкторе TMethod*/
TEST_F(TMethodTest, throws_when_create_with_not_positive_MaxNumOfTrials)
{  
  ASSERT_ANY_THROW(TMethod method(0, eps, r, reserv, m, L, curl, task, pData));
}

TEST_F(TMethodTest, throws_when_create_with_not_positive_epsilon)
{  
  ASSERT_ANY_THROW(TMethod method(MaxNumOfTrials, 0, r, reserv, m, L, curl, task, pData));
}

TEST_F(TMethodTest, throws_when_create_with_too_large_epsilon)
{  
  ASSERT_ANY_THROW(TMethod method(MaxNumOfTrials, 0.011, r, reserv, m, L, curl, task, pData));
}

TEST_F(TMethodTest, throws_when_create_with_too_low_r)
{  
  ASSERT_ANY_THROW(TMethod method(MaxNumOfTrials, eps, 2, reserv, m, L, curl, task, pData));
}

TEST_F(TMethodTest, throws_when_create_with_negative_reserv)
{  
  ASSERT_ANY_THROW(TMethod method(MaxNumOfTrials, eps, r, -0.001, m, L, curl, task, pData));
}

TEST_F(TMethodTest, throws_when_create_with_too_large_reserv)
{
  ASSERT_ANY_THROW(TMethod method(MaxNumOfTrials, eps, r, 0.011, m, L, curl, task, pData));
}

TEST_F(TMethodTest, throws_when_create_with_too_low_m)
{  
  ASSERT_ANY_THROW(TMethod method(MaxNumOfTrials, eps, r, reserv, 1, L, curl, task, pData));
}

TEST_F(TMethodTest, throws_when_create_with_too_large_m)
{
  ASSERT_ANY_THROW(TMethod method(MaxNumOfTrials, eps, r, reserv, MaxM + 1, L, curl, task, pData));
}

TEST_F(TMethodTest, throws_when_create_with_not_positive_L)
{  
  ASSERT_ANY_THROW(TMethod method(MaxNumOfTrials, eps, r, reserv, m, 0, curl, task, pData));
}

TEST_F(TMethodTest, can_create_with_correct_values)
{
  ASSERT_NO_THROW(TMethod method(MaxNumOfTrials, eps, r, reserv, m, L, curl, task, pData));
}