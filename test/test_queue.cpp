#include "queue.h"
#include <gtest.h>

#define MAXSIZE 1023
class TQueueTest : public ::testing::Test 
{
protected:
  TPriorityQueue* queue;
  TQueueTest() :  queue(0) {}

  void CreateQueue(int maxSize = MAXSIZE) 
  {
    queue = new TPriorityQueue(maxSize);  
  }

  ~TQueueTest()
  {
    delete queue;
  }
};

TEST_F(TQueueTest, throws_when_create_with_max_size_queue_not_divisible_by_power_of_two)
{
  ASSERT_ANY_THROW(TPriorityQueue q(10));
}

TEST_F(TQueueTest, can_create_queue_with_correct_values)
{
  ASSERT_NO_THROW(TPriorityQueue q(1023));
}

TEST_F(TQueueTest, can_create_an_empty_queue)
{
  CreateQueue();

  ASSERT_TRUE(queue->IsEmpty());
}

TEST_F(TQueueTest, can_push_element)
{
  CreateQueue();

  queue->Push(1, "a");

  ASSERT_EQ(1, queue->GetSize());
}

TEST_F(TQueueTest, can_detect_when_queue_fill)
{
  CreateQueue(3);
  queue->Push(1, "a");
  queue->Push(2, "b");
  queue->Push(3, "c");

  ASSERT_TRUE(queue->IsFull());
}

TEST_F(TQueueTest, can_detect_when_queue_not_fill)
{
  CreateQueue(3);
  queue->Push(1, "a");
  queue->Push(2, "b");

  ASSERT_FALSE(queue->IsFull());
}

TEST_F(TQueueTest, can_pop_element)
{
  double key;
  void* value;
  char* resValue = "b";
  CreateQueue(3);
  queue->Push(1, "a");
  queue->Push(2, resValue);

  queue->Pop(&key, &value);

  ASSERT_EQ(2, key);
  ASSERT_EQ(resValue, (char*)value);
}

TEST_F(TQueueTest,throw_when_pop_element_from_queue_IsEmpty)
{
  double key;
  void* value;
  CreateQueue(3);

  ASSERT_ANY_THROW(queue->Pop(&key, &value));
}

TEST_F(TQueueTest, not_doing_push_when_queue_IsFull_and_insert_element_with_min_key)
{
  double key;
  void* value;
  CreateQueue(3);
  queue->Push(2, "b");
  queue->Push(3, "c");
  queue->Push(4, "d");

  queue->Push(1, "a");

  queue->Pop(&key, &value);
  ASSERT_NE(1, key);
}

TEST_F(TQueueTest, can_replace_element_with_minimum_key_when_push_to_fill_queue_insert_element_with_not_min_key)
{
  double key;
  void* value;
  CreateQueue(3);
  queue->Push(1, "a");
  queue->Push(2, "b");
  queue->Push(3, "c");

  queue->Push(4, "d");

  queue->Pop(&key, &value);
  ASSERT_EQ(4, key);
}

TEST_F(TQueueTest, can_push_with_priority_element_to_empty_queue)
{
  double key;
  void* value;
  CreateQueue(3);

  queue->PushWithPriority(1, "a");

  ASSERT_FALSE(queue->IsEmpty());
}

TEST_F(TQueueTest, can_push_with_priority_element_to_queue_when_curretn_key_large_then_key_of_min_element)
{
  double key;
  void* value;
  CreateQueue(3);
  queue->PushWithPriority(1, "a");
  queue->PushWithPriority(1, "b");

  queue->PushWithPriority(2, "c");

  queue->Pop(&key, &value);
  ASSERT_EQ(2, key);
}

TEST_F(TQueueTest, can_push_with_priority_element_to_queue_when_curretn_key_equel_key_of_min_element)
{
  double key;
  void* value;
  char* resValue = "c";
  CreateQueue(3);
  queue->PushWithPriority(1, "a");
  queue->PushWithPriority(2, "b");

  queue->PushWithPriority(1, resValue);

  queue->Pop(&key, &value);
  queue->Pop(&key, &value);
  ASSERT_EQ(1, key);
  ASSERT_EQ(resValue, (char*)value);
}

TEST_F(TQueueTest, can_replace_element_with_min_key_when_push_with_priority_element_wiht_large_to_fill_queue)
{
  double key;
  void* value;
  char* resValue = "d";
  CreateQueue(3);
  queue->PushWithPriority(1, "a");
  queue->PushWithPriority(1, "b");
  queue->PushWithPriority(3, "c");

  queue->PushWithPriority(2, "d");

  queue->Pop(&key, &value);
  queue->Pop(&key, &value);
  ASSERT_EQ(2, key);
  ASSERT_EQ(resValue, (char*)value);
}

TEST_F(TQueueTest, can_clear_queue)
{  
  CreateQueue(3);
  queue->Push(1, "a");
  queue->Push(1, "b");
  queue->Push(3, "c");

  queue->Clear();

  ASSERT_TRUE(queue->IsEmpty());
}
