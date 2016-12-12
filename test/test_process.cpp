#include <gtest.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "mpi.h"
#include "process.h"
#include "common.h"
#include "test_common.h"
#include "problem_manager.h"
using namespace std;

#define RASTRIGIN_PATH "problems/rastrigin/rastrigin.dll"
#define TESTDATA_PATH "testData/"

/**
  Вспомогательный класс, помогающий задать начальную конфигурацию объекта класса #TProcess,
  которая будет использоваться в тестах
 */
struct testParameters
{
  std::string libName;
  //std::string actualDataFile;
  std::string expectedDataFile;
  int dim;
  testParameters(std::string _libName,
                 /*std::string _actualDataFile,*/
                 std::string _expectedDataFile,
                 int _dim): 
  libName(_libName),/* actualDataFile(_actualDataFile),*/ expectedDataFile(_expectedDataFile), dim(_dim) {}
};
// ------------------------------------------------------------------------------------------------
class TProcessTest : public ::testing::TestWithParam<testParameters>
{
protected:
  static const int curL = 0;
  static const int L = 1;
  static const int m = 10;
  static const int numPoints = 1;
  static const int n = 4;

  int numOfTaskLevels;
  int maxNumOfPounts[2];
  int dimInTaskLevel[2];
  int childInProcLevel[2];
  double r;
  double reserv;
  double eps[2];

  TProcess* pProcess;
  int ProcRank, ProcNum;
  TProblemManager manager;
  IProblem* problem;
  void SetUp()
  {
    SetUp(std::string(RASTRIGIN_PATH), n);
  }

  void TearDown()
  {
  }

  void SetUp(string libName, int n)
  {
    int NumOfFuncs = 1;
    r = 2.3;
    reserv = 0.001;
    eps[0] = eps[1] = 0.01;
    numOfTaskLevels = 1;
    maxNumOfPounts[0] = maxNumOfPounts[1] = 10000;
    dimInTaskLevel[0] = n;
    dimInTaskLevel[1] = 0;
    childInProcLevel[0] = childInProcLevel[1] = 0;
    FILE* configFile = fopen("test_config.txt","r");
    char path[255];
    fscanf(configFile, "%s", &path);
    fclose(configFile);

    std::string libPath = std::string(path)+ RASTRIGIN_PATH;
    if (TProblemManager::OK_ == manager.LoadProblemLibrary(libPath))
    {
      problem = manager.GetProblem();
      problem->SetDimension(n);
      /*problem->SetConfigPath(NULL);*/
      problem->Initialize();
    }
    if (MPI_Comm_size(MPI_COMM_WORLD, &ProcNum) != MPI_SUCCESS)
    {
      throw EXCEPTION("Error in MPI_Comm_size call");
    }
    if (MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank) != MPI_SUCCESS)
    {
      throw EXCEPTION("Error in MPI_Comm_rank call");
    }
  }
};

/**
 * Проверка параметра Количество уровней в дереве #NumOfTaskLevels
 * NumOfTaskLevels >=1
 */
TEST_F(TProcessTest, throws_when_create_with_not_positive_NumOfTaskLevels)
{
  if (ProcRank == 0)
  {
    ASSERT_ANY_THROW(new TProcess(problem, 0,
                                  dimInTaskLevel, childInProcLevel, 
                                  maxNumOfPounts, eps, r, m, false, true));
  }
}

/**
 * Проверка параметра надежности метода #r
 * r > 2
 */
TEST_F(TProcessTest, throws_when_create_with_r_out_of_range)
{
  if (ProcRank == 0)
  {
    ASSERT_ANY_THROW(new TProcess(problem, numOfTaskLevels,
                                  dimInTaskLevel, childInProcLevel, 
                                  maxNumOfPounts, eps, 2, m, false, true));
  }
}

/**
 * Проверка параметра Плотность построения развертки #m
 * 2 <= m <= MaxM
 */
TEST_F(TProcessTest, throws_when_create_with_m_out_of_range)
{
  if (ProcRank == 0)
  {
    ASSERT_ANY_THROW(new TProcess(problem, numOfTaskLevels,
                                dimInTaskLevel, childInProcLevel, 
                                maxNumOfPounts, eps, r, 1, false, true));
  }
}

/**
 * Проверка параметра Точность решения задачи #Eps
 * Eps > 0
 */
TEST_F(TProcessTest, throws_when_create_with_eps_out_of_range)
{
  if (ProcRank == 0)
  {
    eps[0] = 0.0;
    ASSERT_ANY_THROW(new TProcess(problem, numOfTaskLevels,
                                dimInTaskLevel, childInProcLevel, 
                                maxNumOfPounts, eps, r, m, false, true));
  }
}

/**
 * Проверка параметра максимальное число итераций для процессов на каждом уровне #MaxNumOfPoints
 * MaxNumOfPoints > 0
 */
TEST_F(TProcessTest, throws_when_create_with_MaxNumOfPoints_out_of_range)
{
  if (ProcRank == 0)
  {
    maxNumOfPounts[0] = 0;
    ASSERT_ANY_THROW(new TProcess(problem, numOfTaskLevels,
                                dimInTaskLevel, childInProcLevel, 
                                maxNumOfPounts, eps, r, m, false, true));
  }
}

/**
 * Проверка параметра Размерность процессов на каждом уровне #DimInTaskLevel
 * DimInTaskLevel > 0
 * сумма размерностей на всех уровнях = общей размерности
 */
TEST_F(TProcessTest, throws_when_create_with_DimInTaskLevel_out_of_range)
{
  if (ProcRank == 0)
  {
    dimInTaskLevel[0] = 0;
    ASSERT_ANY_THROW(new TProcess(problem, numOfTaskLevels,
                                dimInTaskLevel, childInProcLevel, 
                                maxNumOfPounts, eps, r, m, false, true));
  }
}

TEST_F(TProcessTest, throws_when_create_with_illegal_value_DimInTaskLevel)
{
  if (ProcRank == 0)
  {
    numOfTaskLevels = 2;
    dimInTaskLevel[0] = 2;
    dimInTaskLevel[1] = 1;
    childInProcLevel[0] = 3;

    ASSERT_ANY_THROW(new TProcess(problem, numOfTaskLevels,
                                  dimInTaskLevel, childInProcLevel, 
                                  maxNumOfPounts, eps, r, m, false, true));
  }
}

/**
 * Проверка параметра Размерность процессов на каждом уровне #ChildInProcLevel
 * ChildInProcLevel >=0 0
 * сумма размерностей на всех уровнях = общей размерности
 */
TEST_F(TProcessTest, throws_when_create_with_ChildInProcLevel_out_of_range)
{
  if (ProcRank == 0)
  {
    childInProcLevel[0] = -1;
    ASSERT_ANY_THROW(new TProcess(problem, numOfTaskLevels,
                                  dimInTaskLevel, childInProcLevel, 
                                  maxNumOfPounts, eps, r, m, false, true));
  }
}

// работает при запуске 4х процессов
TEST_F(TProcessTest, throws_when_create_with_illegal_value_ChildInProcLevel)
{
  numOfTaskLevels = 2;
  dimInTaskLevel[0] = dimInTaskLevel[2] = 2;
  childInProcLevel[0] = 2;

  if (ProcNum == 4)
  {
    ASSERT_ANY_THROW(new TProcess(problem, numOfTaskLevels,
                                  dimInTaskLevel, childInProcLevel, 
                                  maxNumOfPounts, eps, r, m, false, true));
  }
  else
  {
    ASSERT_TRUE(true);
  }
}
/**
 * Создание процесса с корректными входными параметрами
 * работает при запуске 4х процессов
 */
TEST_F(TProcessTest, no_throws_when_create_with_correct_values)
{
  numOfTaskLevels = 2;
  dimInTaskLevel[0] = dimInTaskLevel[1] = 2;
  childInProcLevel[0] = 3;
  if (ProcNum == 4)
  {
    ASSERT_NO_THROW(new TProcess(problem, numOfTaskLevels,
                                  dimInTaskLevel, childInProcLevel, 
                                  maxNumOfPounts, eps, r, m, false, true));
  }
  else
  {
    ASSERT_TRUE(true);
  }
}
/**
 * Проверка решения задач
 */
TEST_F(TProcessTest, check_states_of_process)
{
  std::string actualDataFile;
  std::string expectedDataFile;
  if (ProcRank == 0)
  {
    actualDataFile = "current_state.dat";
    FILE* configFile = fopen("test_config.txt","r");
    char path[255];
    fscanf(configFile, "%s", &path);
    fclose(configFile);
    if (ProcNum == 1)
    {
      expectedDataFile = std::string(path) + std::string(TESTDATA_PATH) +
        std::string("expectedRastriginState.dat");
    }
    else
    {
      expectedDataFile = std::string(path) + std::string(TESTDATA_PATH) +
        std::string("expectedRastriginStateTree.dat");
    }

    FILE* currentf = fopen(actualDataFile.c_str(),"w");
    fclose(currentf);
  }
  if (ProcNum == 4)
  {
    numOfTaskLevels = 2;
    dimInTaskLevel[0] = dimInTaskLevel[1] = 2;
    childInProcLevel[0] = 3;
  }
 
  if ((ProcNum == 4) || (ProcNum == 1))
  {
    TProcess* pProcess = new TProcess(problem, numOfTaskLevels,
                                       dimInTaskLevel, childInProcLevel, 
                                       maxNumOfPounts, eps, r, m, false, true);

    pProcess->Solve();
    if (ProcRank == 0)
    {
      CheckMetodIteration(expectedDataFile, actualDataFile,
                          pProcess->GetIterationCountRoot() / 10);
    }
    delete pProcess;
  }
}
