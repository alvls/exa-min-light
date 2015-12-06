#include "method.h"
#include "testFunction.h"
#include "Rastrigin.h"
#include <gtest.h>

#define _USE_MATH_DEFINES
#include <math.h>


#define _EPS 0.01
#define _MAX_NUM_OF_TRAILS 10000
#define _R 2.3
#define _RESERV 0.001
#define _M 10
#define _L 1
#define _NUM_OF_FUNC 1
#define _N 4
#define _CURL 0
// ------------------------------------------------------------------------------------------------
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
      const tFunction f[MaxNumOfFunc] = {objfn};
      pData = new TSearchData(_NUM_OF_FUNC);
      bounds(A,B);
      task = new TTask(_N, _N, _NUM_OF_FUNC, A, B, f);
  }

  void CreateMethod(int MaxNumOfTrials = _MAX_NUM_OF_TRAILS, double eps = _EPS,double r = _R,
      double reserv = _RESERV, int m = _M, int L = _L, int curl = _CURL) 
  {
    method = new TMethod(MaxNumOfTrials, eps, r, reserv, m, L, curl, task, pData); 
    method->SetBounds();
  }

  void ReadIterationFromFile(FILE* pf, int &IterationCount, double &AchievedAccuracy,
      bool &recalc, double &BestTrial_FuncValue, double &BestTrial_x, double* BestTrial_y,
      double &pCurTrials_FuncValue, double &pCurTrials_x, double* pCurTrials_y)
  {
    char tmp[30];
    fscanf(pf, "%s%s%d", tmp, tmp, &IterationCount);
    fscanf(pf, "%s%s%lf", tmp, tmp, &AchievedAccuracy);
    fscanf(pf, "%s%s%b", tmp, tmp, &recalc);
    fscanf(pf, "%s%s%lf", tmp, tmp, &BestTrial_FuncValue);
    fscanf(pf, "%s%s%lf", tmp, tmp, &BestTrial_x);    
    for (int i = 0; i <_N; i++)
    {
        fscanf(pf, "%s%s%lf", tmp, tmp, &BestTrial_y[i]);
    }

    fscanf(pf, "%s%s%lf", tmp, tmp, &pCurTrials_FuncValue);  
    fscanf(pf, "%s%s%lf", tmp, tmp, &pCurTrials_x); 
    for (int i = 0; i < _N; i++)
    {
      fscanf(pf, "%s%s%lf", tmp, tmp, &pCurTrials_y[i]);
    }    
  }

  bool DoIteration()
  {
    bool IsStop;
    method->CalculateIterationPoints();
    IsStop = method->CheckStopCondition();
    method->CalculateFunctionals();
    method->RenewSearchData();
    method->EstimateOptimum();
    method->FinalizeIteration();
    return IsStop;
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
     IsStop = DoIteration();
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
    IsStop = DoIteration();
  }

  ASSERT_LT(method->GetAchievedAccuracy(), current_eps);
}


TEST_F(TMethodTest, check_states_of_method_iterations)
{
  char nameCurrentFile[] = "current_state.dat";
  int IterationCount;
  double AchievedAccuracy;
  bool recalc;
  double BestTrial_FuncValue;
  double BestTrial_x;
  double BestTrial_y[MaxDim];
  double pCurTrials_FuncValue;
  double pCurTrials_x;
  double pCurTrials_y[MaxDim];

  int currentIterationCount;
  double currentAchievedAccuracy;
  bool currentrecalc;
  double currentBestTrial_FuncValue;
  double currentBestTrial_x;
  double currentBestTrial_y[MaxDim];  
  double currentpCurTrials_FuncValue;
  double currentpCurTrials_x;
  double currentpCurTrials_y[MaxDim];

  bool IsStop = false;
  FILE* rightf;

  FILE* currentf = fopen(nameCurrentFile,"w");
  fclose(currentf);

  CreateMethod();

  method->SetBounds();
  method->FirstIteration();

  while (!IsStop)
  {     
    if(method->GetIterationCount() % 10 == 0)
    {  
      method->PrintStateToFile(nameCurrentFile);
    }
    IsStop = DoIteration();
  }

  rightf = fopen("state.dat","r");
  currentf = fopen(nameCurrentFile,"r");
  if(rightf == 0 || currentf == 0)
  {
    ASSERT_TRUE(false);
  }
  else
  { 
    int countOfIterations = method->GetIterationCount() / 10;
    while(countOfIterations > 0)
    {
      ReadIterationFromFile(rightf, IterationCount, AchievedAccuracy, recalc,
          BestTrial_FuncValue, BestTrial_x, BestTrial_y, pCurTrials_FuncValue,
          pCurTrials_x, pCurTrials_y);

      ReadIterationFromFile(currentf, currentIterationCount, currentAchievedAccuracy,
          currentrecalc, currentBestTrial_FuncValue, currentBestTrial_x, currentBestTrial_y,
          currentpCurTrials_FuncValue, currentpCurTrials_x, currentpCurTrials_y);

      ASSERT_EQ(IterationCount, currentIterationCount);
      ASSERT_DOUBLE_EQ(AchievedAccuracy, currentAchievedAccuracy);
      ASSERT_EQ(recalc, currentrecalc);
      ASSERT_DOUBLE_EQ(BestTrial_FuncValue, currentBestTrial_FuncValue);
      ASSERT_DOUBLE_EQ(BestTrial_x, currentBestTrial_x);
      ASSERT_DOUBLE_EQ(pCurTrials_FuncValue, currentpCurTrials_FuncValue);
      ASSERT_DOUBLE_EQ(pCurTrials_x, currentpCurTrials_x);
      for (int i = 0; i < _N; i++)
      {
        ASSERT_DOUBLE_EQ(BestTrial_y[i], currentBestTrial_y[i]);
        ASSERT_DOUBLE_EQ(pCurTrials_y[i], currentpCurTrials_y[i]);
      }

    countOfIterations--;
  }
  fclose(rightf);
  fclose(currentf);
  }
}

 