#include <cppds/vector.hpp>

#include <gtest/gtest.h>

TEST(VectorTest, EmptyVector) {
    cppds::vector<int> v;

    EXPECT_EQ(v.size(), 0);
}

TEST(VectorTest, PushAndAccess) {
    cppds::vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    EXPECT_EQ(v.size(), 3);

    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 30);
}

TEST(VectorTest, ElementAccess) {
    cppds::vector<int> v = {10, 20, 30};

    EXPECT_EQ(v.size(), 3);

    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 30);
}

TEST(VectorTest, Pop) {
    cppds::vector<int> v;

    v.push_back(10);
    v.push_back(20);

    v.pop_back();

    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0], 10);
}

TEST(VectorTest, Clear) {
    cppds::vector<int> v = {10, 20};

    v.clear();

    EXPECT_EQ(v.size(), 0);
}