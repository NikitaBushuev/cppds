#include <cppds/set.hpp>

#include <gtest/gtest.h>

TEST(SetTest, EmptySet) {
    cppds::set<int> s;

    EXPECT_EQ(s.size(), 0);

    EXPECT_TRUE(s.empty());
}

TEST(SetTest, InsertAndContain) {
    cppds::set<int> s;

    s.insert(10);
    s.insert(20);
    s.insert(30);

    EXPECT_EQ(s.size(), 3);

    EXPECT_FALSE(s.empty());

    EXPECT_TRUE(s.contains(10));
    EXPECT_TRUE(s.contains(20));
    EXPECT_TRUE(s.contains(30));
}

TEST(SetTest, ElementContain) {
    cppds::set<int> s = {10, 20, 30};

    EXPECT_EQ(s.size(), 3);

    EXPECT_FALSE(s.empty());

    EXPECT_TRUE(s.contains(10));
    EXPECT_TRUE(s.contains(20));
    EXPECT_TRUE(s.contains(30));
}

TEST(SetTest, Erase) {
    cppds::set<int> s;

    s.insert(10);
    s.insert(20);

    s.erase(20);

    EXPECT_EQ(s.size(), 1);

    EXPECT_FALSE(s.empty());

    EXPECT_TRUE(s.contains(10));
}

TEST(SetTest, Clear) {
    cppds::set<int> s = {10, 20};

    s.clear();

    EXPECT_EQ(s.size(), 0);

    EXPECT_TRUE(s.empty());
}