#include "evolvent.h"
#include <gtest.h>

#define _N 2
#define _m 2
#define _L 1

class TRotatedEvolventTest : public ::testing::Test 
{
protected:
  TRotatedEvolvent* rotatedEvolvent;
  TRotatedEvolventTest() : rotatedEvolvent(0) {}
  void CreateRotatedEvolvent(int N = _N, int m = _m, int L = _L) 
  {
    const double A[] = {-0.5, -0.5, -0.5}, B[] = {0.5, 0.5, 0.5};
    rotatedEvolvent = new TRotatedEvolvent(N, m, L);  
    rotatedEvolvent->SetBounds(A, B);
  }
  ~TRotatedEvolventTest()
  {
    delete rotatedEvolvent;
  }
};

TEST_F(TRotatedEvolventTest, throws_when_create_with_negative_N)
{
  ASSERT_ANY_THROW(TRotatedEvolvent ev(-1, _m, _L));
}

TEST_F(TRotatedEvolventTest, throws_when_create_with_too_large_N)
{
  ASSERT_ANY_THROW(TRotatedEvolvent ev(MaxDim + 1, _m, _L));
}

TEST_F(TRotatedEvolventTest, throws_when_create_with_too_low_m)
{
  ASSERT_ANY_THROW(TRotatedEvolvent ev(_N, 1, _L));
}

TEST_F(TRotatedEvolventTest, throws_when_create_with_too_large_m)
{
  ASSERT_ANY_THROW(TRotatedEvolvent ev(_N, MaxM + 1,  _L));
}

TEST_F(TRotatedEvolventTest, throws_when_create_with_too_low_L)
{
  ASSERT_ANY_THROW(TRotatedEvolvent ev(_N, _m,  0));
}

TEST_F(TRotatedEvolventTest, throws_when_create_with_too_large_L)
{
  ASSERT_ANY_THROW(TRotatedEvolvent ev(_N, _m,  _N * (_N - 1) / 2 + 1));
}

TEST_F(TRotatedEvolventTest, can_create_with_correct_values)
{
  ASSERT_NO_THROW(TRotatedEvolvent ev(_N, _m, _L));
}

TEST_F(TRotatedEvolventTest, can_get_Y_on_correct_X_when_L_is_one)
{    
  const double true_value[_N] = {-0.125, -0.375};
  double x = 0.1;
  double* y = new double[_N];
  CreateRotatedEvolvent(_N, _m, _L);

  rotatedEvolvent->GetImage(x, 0, y);

  for (int i = 0; i < _N; i++)
    EXPECT_EQ(true_value[i], y[i]);
  delete [] y;
}

TEST_F(TRotatedEvolventTest, can_get_Y_on_correct_X_when_N_is_3_EvolventNum_is_0)
{    
  const int N = 3;
  const int L = 2;
  const double true_value[N] = {-0.125, -0.375, -0.125};
  double x = 0.1;
  double* y = new double[N];
  CreateRotatedEvolvent(N, _m, L);

  rotatedEvolvent->GetImage(x, 0, y);

  for (int i = 0; i < N; i++)
    EXPECT_EQ(true_value[i], y[i]);
  delete [] y;
}

TEST_F(TRotatedEvolventTest, can_get_Y_on_correct_X_when_N_is_3_EvolventNum_is_1)
{    
  const int N = 3;
  const int L = 3;
  const double true_value[N] = {0.125, -0.125, -0.125};
  double x = 0.1;
  double* y = new double[N];
  CreateRotatedEvolvent(N, _m, L);

  rotatedEvolvent->GetImage(x, 1, y);

  for (int i = 0; i < N; i++)
    EXPECT_EQ(true_value[i], y[i]);
  delete [] y;
}

TEST_F(TRotatedEvolventTest, can_get_Y_on_correct_X_when_N_is_3_EvolventNum_is_2)
{    
  const int N = 3;
  const int L = 3;
  const double true_value[N] = {-0.125, -0.375, -0.125};
  double x = 0.1;
  double* y = new double[N];
  CreateRotatedEvolvent(N, _m, L);

  rotatedEvolvent->GetImage(x, 2, y);

  for (int i = 0; i < N; i++)
    EXPECT_EQ(true_value[i], y[i]);
  delete [] y;
}

TEST_F(TRotatedEvolventTest, can_get_Y_on_correct_X_when_N_is_3_EvolventNum_is_3)
{    
  const int N = 3;
  const int L = 3;
  const double true_value[N] = {-0.125, -0.125, -0.375};
  double x = 0.1;
  double* y = new double[N];
  CreateRotatedEvolvent(N, _m, L);

  rotatedEvolvent->GetImage(x, 3, y);

  for (int i = 0; i < N; i++)
    EXPECT_EQ(true_value[i], y[i]);
  delete [] y;
}

TEST_F(TRotatedEvolventTest, when_get_Y_on_correct_X_and_N_is_3_first_and_fourth_evolvents_are_equel)
{    
  const int N = 3;
  const int L = 3;

  double x = 0.1;
  double* y_1 = new double[N];
  double* y_4 = new double[N];
  CreateRotatedEvolvent(N, _m, L);

  rotatedEvolvent->GetImage(x, 1, y_1);
  rotatedEvolvent->GetImage(x, 4, y_4);

  for (int i = 0; i < N; i++)
    EXPECT_EQ(y_1[i], y_4[i]);
  delete [] y_1;
  delete [] y_4;
}

TEST_F(TRotatedEvolventTest, can_get_X_on_Y)
{    
  const int N = 3;
  const int L = 3;
  double* x = new double[L];
  double correct_x[] = {0.078125, 0.4375, 0.1875};
  double y[] = {-0.125, -0.125, -0.125};
  CreateRotatedEvolvent(N, _m, L);

  rotatedEvolvent->GetPreimages(y, x);

  for (int i = 0; i < L; i++)
    ASSERT_DOUBLE_EQ(correct_x[i], x[i]);
}