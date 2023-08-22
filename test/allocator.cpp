#include <cppds/allocator.hpp>

#include <gtest/gtest.h>

TEST(AllocatorTest, AllocateAndDeallocate) {
    cppds::allocator<int> alloc;

    int *ptr = alloc.allocate(5);
    ASSERT_NE(ptr, nullptr);

    alloc.deallocate(ptr);
}

TEST(AllocatorTest, Reallocate) {
    cppds::allocator<int> alloc;

    int *ptr = alloc.allocate(5);
    ASSERT_NE(ptr, nullptr);

    int *newPtr = alloc.reallocate(ptr, 10);
    ASSERT_NE(newPtr, nullptr);
    ASSERT_NE(newPtr, ptr);

    alloc.deallocate(newPtr);
}

TEST(AllocatorTest, AllocateTooEnoughMemory) {
    cppds::allocator<int> alloc;

    int *ptr = alloc.allocate(-1);
    ASSERT_EQ(ptr, nullptr);

    alloc.deallocate(ptr);
}