#include "gtest/gtest.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(test, test)
{
    int a = 1;
    int b = 5;
    EXPECT_EQ(a+b,6);
}
