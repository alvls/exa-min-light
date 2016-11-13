#include "task.h"
#include "testFunction.h"
#include <gtest.h>

#define _N 3
#define _FREEN 2
#define _NUMOfFUNC 1

class TTaskTest : public ::testing::Test 
{
protected:
  double A[MaxDim];
  double B[MaxDim];
  tFunction f[MaxNumOfFunc];
  TTask* task;

  TTaskTest(): task(0) 
  {
      f[0] = &function;
      for(int i = 0; i < _N; i++)
      {
        A[i] = -1.1;
        B[i] = 1.2;
      }
  }
  void CreateTask() 
  {
    task = new TTask (_N, _FREEN, _NUMOfFUNC, A, B, f);
  }

  ~TTaskTest()
  {
    delete task;
  }
};

TEST_F(TTaskTest, throws_when_create_with_negative_N)
{
  ASSERT_ANY_THROW(TTask task(-1, _FREEN, _NUMOfFUNC, A, B, f));
}

TEST_F(TTaskTest, throws_when_create_with_null_N)
{
  ASSERT_ANY_THROW(TTask task(0, _FREEN, _NUMOfFUNC, A, B, f));
}

TEST_F(TTaskTest, throws_when_create_with_too_large_N)
{
  ASSERT_ANY_THROW(TTask task(MaxDim + 1, _FREEN, _NUMOfFUNC, A, B, f));
}

TEST_F(TTaskTest, throws_when_create_with_free_N_large_N)
{
  ASSERT_ANY_THROW(TTask task(_N, _N + 1, _NUMOfFUNC, A, B, f));
}

TEST_F(TTaskTest, throws_when_create_with_negative_free_N)
{
  ASSERT_ANY_THROW(TTask task(_N, -1, _NUMOfFUNC, A, B, f));
}

TEST_F(TTaskTest, throws_when_create_with_null_free_N)
{
  ASSERT_ANY_THROW(TTask task(_N, 0, _NUMOfFUNC, A, B, f));
}

TEST_F(TTaskTest, throws_when_create_with_null_NumOfFunc)
{
  ASSERT_ANY_THROW(TTask task(_N, _FREEN, 0, A, B, f));
}

TEST_F(TTaskTest, throws_when_create_with_negative_NumOfFunc)
{
  ASSERT_ANY_THROW(TTask task(_N, _FREEN, -1, A, B, f));
}

TEST_F(TTaskTest, throws_when_create_with_too_large_NumOfFunc)
{
  ASSERT_ANY_THROW(TTask task(_N, _FREEN, MaxNumOfFunc + 1, A, B, f));
}

TEST_F(TTaskTest, throws_when_create_with_null_A)
{
  ASSERT_ANY_THROW(TTask task(_N, _FREEN, _NUMOfFUNC, NULL, B, f));
}

TEST_F(TTaskTest, throws_when_create_with_null_B)
{
  ASSERT_ANY_THROW(TTask task(_N, _FREEN, _NUMOfFUNC, A, NULL, f));
}

TEST_F(TTaskTest, throws_when_create_with_null_function_pointer)
{
  ASSERT_ANY_THROW(TTask task(_N, _FREEN, _NUMOfFUNC, A, B, NULL));
}

TEST_F(TTaskTest, can_create_with_correct_values)
{
  ASSERT_NO_THROW(TTask task(_N, _FREEN, _NUMOfFUNC, A, B, f));
}

TEST_F(TTaskTest, throws_when_set_null_FixedY)
{
  CreateTask();

  ASSERT_ANY_THROW(task->SetFixed(_N - _FREEN, NULL));
}

TEST_F(TTaskTest, set_Fixed_with_correct_value)
{
  CreateTask();

  ASSERT_NO_THROW(task->SetFixed(_N - _FREEN, A));
}