#include <cppds/map.hpp>

#include <gtest/gtest.h>

TEST(MapTest, EmptyMap) {
    cppds::map<float, int> m;

    EXPECT_EQ(m.size(), 0);

    EXPECT_TRUE(m.empty());
}

TEST(MapTest, InsertAndContain) {
    cppds::map<float, int> m;

    m.insert(1.5f, 10);
    m.insert(2.5f, 20);
    m.insert(3.5f, 30);

    EXPECT_EQ(m.size(), 3);

    EXPECT_FALSE(m.empty());

    EXPECT_TRUE(m.contains(1.5f));
    EXPECT_TRUE(m.contains(2.5f));
    EXPECT_TRUE(m.contains(3.5f));
}

TEST(MapTest, ElementContain) {
    cppds::map<float, int> m = {{1.5f, 10}, {2.5f, 20}, {3.5f, 30}};

    EXPECT_EQ(m.size(), 3);

    EXPECT_FALSE(m.empty());

    EXPECT_TRUE(m.contains(1.5f));
    EXPECT_TRUE(m.contains(2.5f));
    EXPECT_TRUE(m.contains(3.5f));
}

TEST(MapTest, Erase) {
    cppds::map<float, int> m;

    m.insert(1.5f, 10);
    m.insert(2.5f, 20);

    m.erase(2.5f);

    EXPECT_EQ(m.size(), 1);

    EXPECT_FALSE(m.empty());

    EXPECT_TRUE(m.contains(1.5));
}

TEST(MapTest, Clear) {
    cppds::map<float, int> m = {{1.5f, 10}, {2.5f, 20}};

    m.clear();

    EXPECT_EQ(m.size(), 0);

    EXPECT_TRUE(m.empty());
}