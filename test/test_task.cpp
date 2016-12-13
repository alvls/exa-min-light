#include "task.h"
#include "problem_manager.h"

#include <gtest.h>
#include <string>
#include <cstdlib>

#define RASTRIGIN_PATH "..//problems//rastrigin//rastrigin.dll"
/**
  Вспомогательный класс, помогающий задать начальную конфигурацию объекта класса #TTask,
  которая будет использоваться в тестах
 */
class TTaskTest : public ::testing::Test
{
protected:
  /// Размерность задачи
  static const int n = 5;
  /// Размерность подзадачи
  static const int freeN = 2;
  /// Число функционалов
  static const int numOfFunc = 1;
  /// Левая граница области поиска
  double A[MaxDim];
  /// Правая граница области поиска
  double B[MaxDim];
  /// Указатель на задачу
  TTask* task;
  //Функционалы
  IProblem* problem;
  TProblemManager manager;

  void SetUp()
  {
    std::string libPath = RASTRIGIN_PATH;
    if (TProblemManager::OK_ == manager.LoadProblemLibrary(libPath))
    {
      problem = manager.GetProblem();
      problem->SetDimension(n);
      task = new TTask(n, freeN, problem);
    }
    else
      task = NULL;
  }

  void TearDown()
  {
    delete task;
  }
};

/**
 * Проверка параметра размерности задачи N
 * 1<= N <= MaxDim
 */
TEST_F(TTaskTest, throws_when_create_with_negative_N)
{
  ASSERT_ANY_THROW(TTask testTask(-1, freeN, problem));
}

TEST_F(TTaskTest, throws_when_create_with_null_N)
{
  ASSERT_ANY_THROW(TTask testTask(0, freeN, problem));
}

TEST_F(TTaskTest, throws_when_create_with_too_large_N)
{
  ASSERT_ANY_THROW(TTask testTask(MaxDim + 1, freeN, problem));
}

TEST_F(TTaskTest, throws_when_create_with_free_N_large_N)
{
  ASSERT_ANY_THROW(TTask testTask(n, n + 1, problem));
}

/**
 * Проверка параметра размерности подзадачи FreeN
 * 1<= FreeN <= N
 */
TEST_F(TTaskTest, throws_when_create_with_negative_free_N)
{
  ASSERT_ANY_THROW(TTask testTask(n, -1, problem));
}

TEST_F(TTaskTest, throws_when_create_with_null_free_N)
{
  ASSERT_ANY_THROW(TTask testTask(n, 0, problem));
}

/**
 * Создание задачи с корректными входными параметрами
 */
TEST_F(TTaskTest, can_create_with_correct_values)
{
  ASSERT_NO_THROW(TTask testTask(n, freeN, problem));
}

/**
 * Проверка функции #SetFixed
 * FixedN == N - FreeN; FixedY != NULL
 */
/*
TEST_F(TTaskTest, throws_when_set_invalid_FixedN_value)
{
  ASSERT_FALSE(task == NULL);
  ASSERT_ANY_THROW(task->SetFixed(n - freeN + 1, A));
}
*/
TEST_F(TTaskTest, throws_when_set_null_FixedY)
{
  ASSERT_FALSE(task == NULL);
  ASSERT_ANY_THROW(task->SetFixed(n - freeN, NULL));
}

TEST_F(TTaskTest, set_Fixed_with_correct_value)
{
  ASSERT_FALSE(task == NULL);
  ASSERT_NO_THROW(task->SetFixed(n - freeN, A));
}