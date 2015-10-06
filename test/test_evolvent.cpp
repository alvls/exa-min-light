#include "evolvent.h"
#include <gtest.h>

class TEvolventTest : public ::testing::Test 
{
protected:
  TEvolvent* evolvent;
  TEvolventTest() : evolvent(0) {}
  void CreateEvolvent(int N, int m) 
  {
    const double A[] = {-0.5, -0.5}, B[] = {0.5, 0.5};
    evolvent = new TEvolvent(N, m);  
    evolvent->SetBounds(A, B);
  }
  ~TEvolventTest()
  {
    delete evolvent;
  }
};


/*Проверка входных параметров в конструкторе TEvolvent(int _N, int _m)*/
TEST_F(TEvolventTest, throws_when_create_with_negative_N)
{
  ASSERT_ANY_THROW(TEvolvent ev(-1, 10));
}

TEST_F(TEvolventTest, throws_when_create_with_too_large_N)
{
  ASSERT_ANY_THROW(TEvolvent ev(MaxDim + 1, 10));
}

TEST_F(TEvolventTest, throws_when_create_with_too_low_m)
{
  ASSERT_ANY_THROW(TEvolvent ev(2, 1));
}

TEST_F(TEvolventTest, throws_when_create_with_too_large_m)
{
  ASSERT_ANY_THROW(TEvolvent ev(2, MaxM + 1));
}

TEST_F(TEvolventTest, can_create_with_correct_values)
{
  ASSERT_NO_THROW(TEvolvent ev(MaxDim - 1, MaxM - 1));
}

/*Проверка GetImage(const double& x, double* _y)*/
TEST_F(TEvolventTest, can_get_Y_on_correct_X)
{    
  const int N = 2, m = 2;
  const double true_value[N] = {-0.125, -0.375};
  double x = 0.1;
  double* y = new double[N];
  CreateEvolvent(N, m);
  evolvent->GetImage(x, y);
  for (int i = 0; i < N; i++)
    EXPECT_EQ(true_value[i], y[i]);
  delete [] y;
}

TEST_F(TEvolventTest, throws_when_get_image_with_negative_x)
{    
  const int N = 2, m = 2;
  double x = -1;
  double* y = new double[N];
  CreateEvolvent(N, m);
  ASSERT_ANY_THROW(evolvent->GetImage(x, y));
  delete [] y;
}

TEST_F(TEvolventTest, throws_when_get_image_with_too_large_x)
{    
  const int N = 2, m = 2;
  double x = 2;
  double* y = new double[N];
  CreateEvolvent(N, m);
  ASSERT_ANY_THROW(evolvent->GetImage(x, y));
  delete []y;
}
