#include <gtest/gtest.h>
#include "../Queue.h"

// Initial sample taken from https://github.com/nordlow/gtest-tutorial
class QueueTest : public ::testing::Test {
	 protected:
		  virtual void SetUp() {
		    q1_.Push(1);
		    q2_.Push(2);
		    q2_.Push(3);
		  }

		  // virtual void TearDown() {}

		  Queue<int> q0_{Queue<int>(2)};
		  Queue<int> q1_{Queue<int>(2)};
		  Queue<int> q2_{Queue<int>(2)};
};

// Test initial status of each 
TEST_F(QueueTest, InitialStatus) {
  EXPECT_EQ(0, q0_.Count());
  EXPECT_TRUE(q0_.IsEmpty());
  EXPECT_FALSE(q0_.IsFull());

  EXPECT_EQ(1, q1_.Count());
  EXPECT_FALSE(q1_.IsEmpty());
  EXPECT_FALSE(q1_.IsFull());

  EXPECT_EQ(2, q2_.Count());
  EXPECT_FALSE(q2_.IsEmpty());
  EXPECT_TRUE(q2_.IsFull());
}

// Testing Pop method in various contexts
TEST_F(QueueTest, PopWorks) {
	// Poping from empty Queue returns logic_error
	EXPECT_THROW(q0_.Pop(), std::logic_error);
	EXPECT_EQ(0, q0_.Count());
	EXPECT_TRUE(q0_.IsEmpty());
	EXPECT_FALSE(q0_.IsFull());

	int n;

	// Removes last element of q1
	n = q1_.Pop();
	EXPECT_EQ(1, n);
	EXPECT_EQ(0, q1_.Count());
	EXPECT_TRUE(q1_.IsEmpty());
	EXPECT_FALSE(q1_.IsFull());
	// Removes one element of q2
	n = q2_.Pop();
	EXPECT_EQ(2, n);
	EXPECT_EQ(1, q2_.Count());
	EXPECT_FALSE(q2_.IsEmpty());
	EXPECT_FALSE(q2_.IsFull());
}

// Testing Push method in various contexts
TEST_F(QueueTest, PushWorks) {
	// Adding negative element and removing it back
	q0_.Push(-5);
	EXPECT_EQ(1, q0_.Count());
	EXPECT_EQ(-5, q0_.Pop());
	EXPECT_TRUE(q0_.IsEmpty());

	int n;

	// Adding one more element to q1 to make it full
	q1_.Push(1);
	EXPECT_FALSE(q1_.IsEmpty());
	EXPECT_TRUE(q1_.IsFull());

	// Adding value to full Queue (ignored)
	EXPECT_TRUE(q2_.IsFull());
	q2_.Push(2);
	EXPECT_TRUE(q2_.IsFull());
	EXPECT_EQ(2, q2_.Count());
}

// Testing ToString method in various contexts
TEST_F(QueueTest, ToStringWorks) {
	// Expected print with initial config
	EXPECT_EQ("", q0_.ToString());
	EXPECT_EQ("1", q1_.ToString());
	EXPECT_EQ("2,3", q2_.ToString());
	// Pop one element from q2
	q2_.Pop();
	EXPECT_EQ("3", q2_.ToString());
	// Pop one element from q1
	q1_.Pop();
	EXPECT_EQ("", q1_.ToString());
	// Pushing one element to q0
	q0_.Push(5);
	EXPECT_EQ("5", q0_.ToString());
}



