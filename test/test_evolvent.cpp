#include "evolvent.h"

#include <gtest.h>

class TEvolventTest : public ::testing::Test 
{
 protected:
    TEvolvent* evolvent;
    TEvolventTest() : evolvent() {}
    void SetValue(int N, int m) 
    {
        evolvent = new TEvolvent(N, m);        
    }
};


/*Проверка входных параметров в конструкторе TEvolvent(int _N, int _m)*/
TEST_F(TEvolventTest, throws_when_get_wrong_value_N)
{
    ASSERT_ANY_THROW(SetValue(-1, 3));
}

TEST_F(TEvolventTest, throws_when_get_wrong_value_m)
{
    ASSERT_ANY_THROW(SetValue(2, MaxM + 1));
}

TEST_F(TEvolventTest, throws_when_get_wrong_values_N_m)
{
    ASSERT_ANY_THROW(SetValue(MaxDim + 1, 1));
}

TEST_F(TEvolventTest, throws_when_get_correct_values_N_m)
{
    ASSERT_NO_THROW(SetValue(MaxDim - 1, MaxM - 1));
}

/*???Проверка SetBounds(const double* _A, const double* _B)*/



/*Проверка GetImage(const double& x, double* _y)*/
TEST_F(TEvolventTest, can_get_correct_Y_on_X)
{    
    const int N = 2, m = 2;
    const double A[] = {-0.5, -0.5}, B[] = {0.5, 0.5};
    const double true_value[N] = {-0.125, -0.375};
    double x = 0.1;
    double* y = new double[N];
    SetValue(N, m);
    evolvent->SetBounds(A, B);
    evolvent->GetImage(x, y);
    for(int i = 0; i < N; i++)
        EXPECT_EQ(true_value[i], y[i]);
    delete []y;
}

//TEST(TSet, can_get_max_power_set)
//{
//  const int size = 5;
//  TSet set(size);
//
//  EXPECT_EQ(size, set.GetMaxPower());
//}
//
//TEST(TSet, can_insert_non_existing_element)
//{
//  const int size = 5, k = 3;
//  TSet set(size);
//  set.InsElem(k);
//
//  EXPECT_NE(set.IsMember(k), 0);
//}
//
//TEST(TSet, can_insert_existing_element)
//{
//  const int size = 5;
//  const int k = 3;
//  TSet set(size);
//  set.InsElem(k);
//  set.InsElem(k);
//
//  EXPECT_NE(set.IsMember(k), 0);
//}
//
//TEST(TSet, can_delete_non_existing_element)
//{
//  const int size = 5, k = 3;
//  TSet set(size);
//  set.DelElem(k);
//
//  EXPECT_EQ(set.IsMember(k), 0);
//}
//
//TEST(TSet, can_delete_existing_element)
//{
//  const int size = 5, k = 3;
//  TSet set(size);
//
//  set.InsElem(k);
//  EXPECT_GT(set.IsMember(k), 0);
//
//  set.DelElem(k);
//  EXPECT_EQ(set.IsMember(k), 0);
//}
//
//TEST(TSet, compare_two_sets_of_non_equal_sizes)
//{
//  const int size1 = 4, size2 = 6;
//  TSet set1(size1), set2(size2);
//
//  EXPECT_EQ(1, set1 != set2);
//}
//
//TEST(TSet, compare_two_equal_sets)
//{
//  const int size = 4;
//  TSet set1(size), set2(size);
//  // set1 = set2 = {1, 3}
//  set1.InsElem(1);
//  set1.InsElem(3);
//  set2.InsElem(1);
//  set2.InsElem(3);
//
//  EXPECT_EQ(set1, set2);
//}
//
//TEST(TSet, compare_two_non_equal_sets)
//{
//  const int size = 4;
//  TSet set1(size), set2(size);
//  // set1 = {1, 3}
//  set1.InsElem(1);
//  set1.InsElem(3);
//  // set2 = {1, 2}
//  set2.InsElem(1);
//  set2.InsElem(2);
//
//  EXPECT_EQ(1, set1 != set2);
//}
//
//TEST(TSet, can_assign_set_of_equal_size)
//{
//  const int size = 4;
//  TSet set1(size), set2(size);
//  // set1 = {1, 3}
//  set1.InsElem(1);
//  set1.InsElem(3);
//  set2 = set1;
//
//  EXPECT_EQ(set1, set2);
//}
//
//TEST(TSet, can_assign_set_of_greater_size)
//{
//  const int size1 = 4, size2 = 6;
//  TSet set1(size1), set2(size2);
//  // set1 = {1, 3}
//  set1.InsElem(1);
//  set1.InsElem(3);
//  set2 = set1;
//
//  EXPECT_EQ(set1, set2);
//}
//
//TEST(TSet, can_assign_set_of_less_size)
//{
//  const int size1 = 6, size2 = 4;
//  TSet set1(size1), set2(size2);
//  // set1 = {1, 3, 5}
//  set1.InsElem(1);
//  set1.InsElem(3);
//  set1.InsElem(5);
//  set2 = set1;
//
//  EXPECT_EQ(set1, set2);
//}
//
//TEST(TSet, can_insert_non_existing_element_using_plus_operator)
//{
//  const int size = 4;
//  const int k = 3;
//  TSet set(size), updatedSet(size);
//  set.InsElem(0);
//  set.InsElem(2);
//  updatedSet = set + k;
//
//  EXPECT_NE(0, updatedSet.IsMember(k));
//}
//
//TEST(TSet, throws_when_insert_non_existing_element_out_of_range_using_plus_operator)
//{
//  const int size = 4;
//  const int k = 6;
//  TSet set(size), updatedSet(size);
//  set.InsElem(0);
//  set.InsElem(2);
//
//  ASSERT_ANY_THROW(updatedSet = set + k);
//}
//
//TEST(TSet, can_insert_existing_element_using_plus_operator)
//{
//  const int size = 4;
//  const int k = 3;
//  TSet set(size), updatedSet(size);
//  set.InsElem(0);
//  set.InsElem(k);
//  updatedSet = set + k;
//
//  EXPECT_NE(0, set.IsMember(k));
//}
//
//TEST(TSet, check_size_of_the_combination_of_two_sets_of_equal_size)
//{
//  const int size = 5;
//  TSet set1(size), set2(size), set3(size);
//  // set1 = {1, 2, 4}
//  set1.InsElem(1);
//  set1.InsElem(2);
//  set1.InsElem(4);
//  // set2 = {0, 1, 2}
//  set2.InsElem(0);
//  set2.InsElem(1);
//  set2.InsElem(2);
//  set3 = set1 + set2;
//
//  EXPECT_EQ(size, set3.GetMaxPower());
//}
//
//TEST(TSet, can_combine_two_sets_of_equal_size)
//{
//  const int size = 5;
//  TSet set1(size), set2(size), set3(size), expSet(size);
//  // set1 = {1, 2, 4}
//  set1.InsElem(1);
//  set1.InsElem(2);
//  set1.InsElem(4);
//  // set2 = {0, 1, 2}
//  set2.InsElem(0);
//  set2.InsElem(1);
//  set2.InsElem(2);
//  set3 = set1 + set2;
//  // expSet = {0, 1, 2, 4}
//  expSet.InsElem(0);
//  expSet.InsElem(1);
//  expSet.InsElem(2);
//  expSet.InsElem(4);
//
//  EXPECT_EQ(expSet, set3);
//}
//
//TEST(TSet, check_size_changes_of_the_combination_of_two_sets_of_non_equal_size)
//{
//  const int size1 = 5, size2 = 7;
//  TSet set1(size1), set2(size2), set3(size1);
//  // set1 = {1, 2, 4}
//  set1.InsElem(1);
//  set1.InsElem(2);
//  set1.InsElem(4);
//  // set2 = {0, 1, 2}
//  set2.InsElem(0);
//  set2.InsElem(1);
//  set2.InsElem(2);
//  set3 = set1 + set2;
//
//  EXPECT_EQ(size2, set3.GetMaxPower());
//}
//
//TEST(TSet, can_combine_two_sets_of_non_equal_size)
//{
//  const int size1 = 5, size2 = 7;
//  TSet set1(size1), set2(size2), set3(size1), expSet(size2);
//  // set1 = {1, 2, 4}
//  set1.InsElem(1);
//  set1.InsElem(2);
//  set1.InsElem(4);
//  // set2 = {0, 1, 2, 6}
//  set2.InsElem(0);
//  set2.InsElem(1);
//  set2.InsElem(2);
//  set2.InsElem(6);
//  set3 = set1 + set2;
//  // expSet = {0, 1, 2, 4, 6}
//  expSet.InsElem(0);
//  expSet.InsElem(1);
//  expSet.InsElem(2);
//  expSet.InsElem(4);
//  expSet.InsElem(6);
//
//  EXPECT_EQ(expSet, set3);
//}
//
//TEST(TSet, can_intersect_two_sets_of_equal_size)
//{
//  const int size = 5;
//  TSet set1(size), set2(size), set3(size), expSet(size);
//  // set1 = {1, 2, 4}
//  set1.InsElem(1);
//  set1.InsElem(2);
//  set1.InsElem(4);
//  // set2 = {0, 1, 2}
//  set2.InsElem(0);
//  set2.InsElem(1);
//  set2.InsElem(2);
//  set3 = set1 * set2;
//  // expSet = {1, 2}
//  expSet.InsElem(1);
//  expSet.InsElem(2);
//
//  EXPECT_EQ(expSet, set3);
//}
//
//TEST(TSet, can_intersect_two_sets_of_non_equal_size)
//{
//  const int size1 = 5, size2 = 7;
//  TSet set1(size1), set2(size2), set3(size1), expSet(size2);
//  // set1 = {1, 2, 4}
//  set1.InsElem(1);
//  set1.InsElem(2);
//  set1.InsElem(4);
//  // set2 = {0, 1, 2, 4, 6}
//  set2.InsElem(0);
//  set2.InsElem(1);
//  set2.InsElem(2);
//  set2.InsElem(4);
//  set2.InsElem(6);
//  set3 = set1 * set2;
//  // expSet = {1, 2, 4}
//  expSet.InsElem(1);
//  expSet.InsElem(2);
//  expSet.InsElem(4);
//
//  EXPECT_EQ(expSet, set3);
//}
//
//TEST(TSet, check_negation_operator)
//{
//  const int size = 4;
//  TSet set(size), set1(size), expSet(size);
//  // set1 = {1, 3}
//  set.InsElem(1);
//  set.InsElem(3);
//  set1 = ~set;
//  // expSet = {0, 2}
//  expSet.InsElem(0);
//  expSet.InsElem(2);
//
//  EXPECT_EQ(expSet, set1);
//}
