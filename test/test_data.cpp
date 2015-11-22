#include "data.h"
#include <gtest.h>

class TSearchDataTest : public ::testing::Test 
{
protected:
  TSearchData* data;
  TSearchDataTest() : data(0) {}
  void CreateSearchData(int NumOfFuncs = MaxNumOfFunc, int MaxSize = DefaultSearchDataSize) 
  {
    data = new TSearchData(NumOfFuncs, MaxSize);
  }
  ~TSearchDataTest()
  {
    delete data;
  }
};


TEST_F(TSearchDataTest, throws_when_create_with_null_NumOfFunc)
{
  ASSERT_ANY_THROW(TSearchData d(0, DefaultSearchDataSize));
}

TEST_F(TSearchDataTest, throws_when_create_with_negative_NumOfFunc)
{
  ASSERT_ANY_THROW(TSearchData d(-1, DefaultSearchDataSize));
}

TEST_F(TSearchDataTest, throws_when_create_with_too_large_NumOfFunc)
{
  ASSERT_ANY_THROW(TSearchData d(MaxNumOfFunc + 1, DefaultSearchDataSize));
}

TEST_F(TSearchDataTest, throws_when_create_with_null_MaxSize_of_searchData)
{
  ASSERT_ANY_THROW(TSearchData d(MaxNumOfFunc, 0));
}

TEST_F(TSearchDataTest, throws_when_create_with_negative_MaxSize_of_searchData)
{
  ASSERT_ANY_THROW(TSearchData d(MaxNumOfFunc, -1));
}

TEST_F(TSearchDataTest, can_create_searchData_with_correct_values)
{
  ASSERT_NO_THROW(TSearchData d(MaxNumOfFunc, DefaultSearchDataSize));
}

TEST_F(TSearchDataTest, can_determine_what_queue_of_global_variables_not_empty)
{
  CreateSearchData();
  data->PushToQueue(new TSearchInterval());
  ASSERT_FALSE(data->IsQueueEmpty());
}

TEST_F(TSearchDataTest, can_determine_what_queue_of_global_variables_is_empty)
{
  CreateSearchData();
  ASSERT_TRUE(data->IsQueueEmpty());
}

TEST_F(TSearchDataTest, can_determine_what_queue_of_global_variables_not_full)
{
  CreateSearchData();
  data->PushToQueue(new TSearchInterval());
  ASSERT_FALSE(data->IsQueueFull());
}

TEST_F(TSearchDataTest, can_determine_what_queue_of_global_variables_is_full)
{
  CreateSearchData();
  for(int i = 0; i < DefaultQueueSize; i++)
    data->PushToQueue(new TSearchInterval());
  ASSERT_TRUE(data->IsQueueFull());
}

TEST_F(TSearchDataTest, can_insert_interval)
{
  TSearchInterval interval;
  CreateSearchData();
  interval.xl = 3;
  TSearchInterval* pInterval = data->InsertInterval(interval);
  //ASSERT_EQ(1, data->GetCount());
  ASSERT_EQ(interval.xl, pInterval->xl);
}

TEST_F(TSearchDataTest, do_nothing_when_update_interval_which_is_not)
{
  TSearchInterval interval;
  CreateSearchData();
  interval.xl = 3;
  data->UpdateInterval(interval);
  ASSERT_EQ(0, data->GetCount());
}

TEST_F(TSearchDataTest, can_update_interval)
{
  TSearchInterval interval;
  CreateSearchData();
  interval.xl = 3;
  interval.R = 3;
  TSearchInterval* pInterval = data->InsertInterval(interval);
  interval.R = 5;
  data->UpdateInterval(interval);

  ASSERT_EQ(interval.R, pInterval->R);
}

TEST_F(TSearchDataTest, can_get_interval_by_X)
{
  TSearchInterval interval;
  CreateSearchData();
  interval.xl = 1;
  interval.R = 1;
  TSearchInterval* pInterval = data->InsertInterval(interval);
  interval.xl = 3;
  interval.R = 3;
  pInterval = data->InsertInterval(interval);

  ASSERT_EQ(interval.R, data->GetIntervalByX(interval.xl)->R);
}
