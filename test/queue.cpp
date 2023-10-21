#include <cppds/queue.hpp>

#include <gtest/gtest.h>

TEST(QueueTest, EmptyQueue) {
    cppds::queue<int> v;

    EXPECT_EQ(v.size(), 0);
}

TEST(QueueTest, PushAndAccess) {
    cppds::queue<int> v;

    v.push(10);
    EXPECT_EQ(v.back(), 10);

    v.push(20);
    EXPECT_EQ(v.back(), 20);

    v.push(30);
    EXPECT_EQ(v.back(), 30);

    EXPECT_EQ(v.size(), 3);
}

TEST(QueueTest, ElementAcess) {
    cppds::queue<int> v = {10, 20, 30};

    EXPECT_EQ(v.size(), 3);

    EXPECT_EQ(v.front(), 10);
    v.pop();

    EXPECT_EQ(v.front(), 20);
    v.pop();

    EXPECT_EQ(v.front(), 30);
    v.pop();
}

TEST(QueueTest, Clear) {
    cppds::queue<int> v = {10, 20};

    v.clear();

    EXPECT_EQ(v.size(), 0);
}