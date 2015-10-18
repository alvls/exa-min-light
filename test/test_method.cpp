#include "method.h"
#include <gtest.h>

#define _USE_MATH_DEFINES
#include <math.h>


#define _EPS 0.001
#define _MAX_NUM_OF_TRAILS 10000
#define _R 2.3
#define _RESERV 0.001
#define _M 10
#define _L 1
#define _NUM_OF_FUNC 1
#define _N 3
#define _CURL 0

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
  TTask* task;
  TSearchData* pData;

  TMethod* method;
  TMethodTest():  method(0)
  {
      const tFunction f[MaxNumOfFunc] = {&function};
      task = new TTask(_N, _N, _NUM_OF_FUNC, A, B, f);
      pData = new TSearchData(_NUM_OF_FUNC);
      for(int i = 0; i < MaxDim; i++)
      {
        A[i] = -1.1;
        B[i] = 1.2;
      }
  }

  void CreateMethod(int MaxNumOfTrials = _MAX_NUM_OF_TRAILS, double eps = _EPS,double r = _R, double reserv = _RESERV, int m = _M, int L = _L, int curl = _CURL) 
  {
    method = new TMethod(MaxNumOfTrials, eps, r, reserv, m, L, curl, task, pData); 
    method->SetBounds();
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
  ASSERT_ANY_THROW(TMethod method(0, _EPS, _R, _RESERV, _M, _L, _CURL, task, pData));
}

TEST_F(TMethodTest, throws_when_create_with_not_positive_epsilon)
{  
  ASSERT_ANY_THROW(TMethod method(_MAX_NUM_OF_TRAILS, 0, _R, _RESERV, _M, _L, _CURL, task, pData));
}

TEST_F(TMethodTest, throws_when_create_with_too_large_epsilon)
{  
  ASSERT_ANY_THROW(TMethod method(_MAX_NUM_OF_TRAILS, 0.011, _R, _RESERV, _M, _L, _CURL, task, pData));
}

TEST_F(TMethodTest, throws_when_create_with_too_low_r)
{  
  ASSERT_ANY_THROW(TMethod method(_MAX_NUM_OF_TRAILS, _EPS, 2, _RESERV, _M, _L, _CURL, task, pData));
}

TEST_F(TMethodTest, throws_when_create_with_negative_reserv)
{  
  ASSERT_ANY_THROW(TMethod method(_MAX_NUM_OF_TRAILS, _EPS, _R, -0.001, _M, _L, _CURL, task, pData));
}

TEST_F(TMethodTest, throws_when_create_with_too_large_reserv)
{
  ASSERT_ANY_THROW(TMethod method(_MAX_NUM_OF_TRAILS, _EPS, _R, 0.011, _M, _L, _CURL, task, pData));
}

TEST_F(TMethodTest, throws_when_create_with_too_low_m)
{  
  ASSERT_ANY_THROW(TMethod method(_MAX_NUM_OF_TRAILS, _EPS, _R, _RESERV, 1, _L, _CURL, task, pData));
}

TEST_F(TMethodTest, throws_when_create_with_too_large_m)
{
  ASSERT_ANY_THROW(TMethod method(_MAX_NUM_OF_TRAILS, _EPS, _R, _RESERV, MaxM + 1, _L, _CURL, task, pData));
}

TEST_F(TMethodTest, throws_when_create_with_not_positive_L)
{  
  ASSERT_ANY_THROW(TMethod method(_MAX_NUM_OF_TRAILS, _EPS, _R, _RESERV, _M, 0, _CURL, task, pData));
}

TEST_F(TMethodTest, can_create_with_correct_values)
{
  ASSERT_NO_THROW(TMethod method(_MAX_NUM_OF_TRAILS, _EPS, _R, _RESERV, _M, _L, _CURL, task, pData));
}

/*Проверка FirstIteration*/
TEST_F(TMethodTest, on_FirstIteration_can_reset_IterationCount)
{
  CreateMethod();
  method->FirstIteration();
  ASSERT_EQ(1, method->GetIterationCount()); 
}

TEST_F(TMethodTest, on_FirstIterationcan_reset_BestTrial)
{
  CreateMethod();
  method->FirstIteration();
  ASSERT_EQ(-2, method->GetOptimEstimation().index);
}

TEST_F(TMethodTest, on_FirstIterationcan_reset_NumberOfTrials)
{
  CreateMethod();
  method->FirstIteration();
  ASSERT_EQ(0, method->GetNumberOfTrials());
}

TEST_F(TMethodTest, on_FirstIteration_can_generate_new_points)
{
  CreateMethod();

  method->FirstIteration();

  int NumPoints = method->GetNumPoints();
  double h = 1.0 / (NumPoints + 1);
  for(int i = 0; i < NumPoints; i++)
    ASSERT_EQ((i + 1) * h, method->GetCurTrials()[i].x);
}


/*Проверка FinalizeIteration*/
TEST_F(TMethodTest, FinalizeIteration_can_increase_iterationCount_1)
{
  CreateMethod();

  method->FirstIteration();
  int count = method->GetIterationCount();
  method->FinalizeIteration();

  ASSERT_EQ( ++count, method->GetIterationCount());
}

/*Проверка CheckStopCondition*/
TEST_F(TMethodTest, CheckStopCondition_can_stop_method_when_too_many_inerations)
{
  int current_MaxNumOfTrials = 2;
  CreateMethod(current_MaxNumOfTrials);

  bool IsStop = false;

  method->FirstIteration();
  while (!IsStop)
  {      
    method->CalculateIterationPoints();
    IsStop = method->CheckStopCondition();
    method->CalculateFunctionals();
    method->RenewSearchData();
    method->EstimateOptimum();
    method->FinalizeIteration();
  }

  ASSERT_GE(method->GetIterationCount(), current_MaxNumOfTrials);
}

TEST_F(TMethodTest, CheckStopCondition_can_stop_method_when_required_accuracy_is_achieved)
{
  double current_eps = 0.01;
  int current_MaxNumOfTrials = 150000;
  CreateMethod(current_MaxNumOfTrials, current_eps);

  bool IsStop = false;

  method->FirstIteration();
  while (!IsStop)
  {      
    method->CalculateIterationPoints();
    IsStop = method->CheckStopCondition();
    method->CalculateFunctionals();
    method->RenewSearchData();
    method->EstimateOptimum();
    method->FinalizeIteration();
  }

  //ASSERT_GE(method->GetIterationCount(), current_MaxNumOfTrials);
  ASSERT_LT(method->GetAchievedAccuracy(), current_eps);
}

  
///*Проверка EstimateOptimum*/
//TEST_F(TMethodTest, EstimateOptimum)
//{
//  CreateMethod();
//  
//  TTrial BestTrial;
//  TTrial* pCurTrials;
//  bool IsStop = false;
//  int NumPoints = method->GetNumPoints();
//  int indexBestTrial = 0;
//  method->FirstIteration();
//  while (!IsStop)
//  {      
//    method->CalculateIterationPoints();
//    IsStop = method->CheckStopCondition();
//    method->CalculateFunctionals();
//    method->RenewSearchData();
//    method->EstimateOptimum();
//    method->FinalizeIteration();
//
//    pCurTrials = method->GetCurTrials();
//
//    for (int i = 1; i < NumPoints; i++)
//    {
//      if (pCurTrials[i].index > pCurTrials[indexBestTrial].index || 
//          pCurTrials[i].index == pCurTrials[indexBestTrial].index && 
//          pCurTrials[i].FuncValues[pCurTrials[indexBestTrial].index] < pCurTrials[indexBestTrial].FuncValues[pCurTrials[indexBestTrial].index])
//      {
//        indexBestTrial = i;
//      }
//    }
//
//    BestTrial = method->GetOptimEstimation();
//    ASSERT_EQ(  BestTrial.index, pCurTrials[indexBestTrial].index);
//    //ASSERT_EQ(  BestTrial.x, pCurTrials[indexBestTrial].x);
//  }
//}  
