#include <cppds/stack.hpp>

#include <gtest/gtest.h>

TEST(StackTest, EmptyStack) {
    cppds::stack<int> v;

    EXPECT_EQ(v.length(), 0);
}

TEST(StackTest, PushAndAccess) {
    cppds::stack<int> v;

    v.push(10);
    EXPECT_EQ(v.top(), 10);

    v.push(20);
    EXPECT_EQ(v.top(), 20);

    v.push(30);
    EXPECT_EQ(v.top(), 30);

    EXPECT_EQ(v.length(), 3);
}

TEST(StackTest, ElementAcess) {
    cppds::stack<int> v = {10, 20, 30};

    EXPECT_EQ(v.length(), 3);

    EXPECT_EQ(v.top(), 30);
    v.pop();

    EXPECT_EQ(v.top(), 20);
    v.pop();

    EXPECT_EQ(v.top(), 10);
    v.pop();
}

TEST(StackTest, Clear) {
    cppds::stack<int> v = {10, 20};

    v.clear();

    EXPECT_EQ(v.length(), 0);
}