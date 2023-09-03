#include <cppds/array.hpp>

#include <gtest/gtest.h>

TEST(ArrayTest, sizeTest) {
    cppds::array<int, 5> arr;

    EXPECT_EQ(arr.size(), 5);
}

TEST(ArrayTest, ElementAccessTest) {
    cppds::array<int, 3> arr = {10, 20, 30};

    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

TEST(ArrayTest, ConstElementAccessTest) {
    const cppds::array<int, 4> constArr = {5, 15, 25, 35};
    
    EXPECT_EQ(constArr[0], 5);
    EXPECT_EQ(constArr[1], 15);
    EXPECT_EQ(constArr[2], 25);
    EXPECT_EQ(constArr[3], 35);
}
