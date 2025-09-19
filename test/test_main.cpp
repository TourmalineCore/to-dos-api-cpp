#include "addition-operation.h"
#include "gtest/gtest.h"

// Testing reference section in GTest documentation
// https://google.github.io/googletest/reference/testing.html
TEST(MathTest, AdditionOperation)
{   
    // Assertions section in GTest documentation
    // https://google.github.io/googletest/reference/assertions.html#EXPECT_EQ
    EXPECT_EQ(AdditionOperation(2, 3), 5);
    EXPECT_EQ(AdditionOperation(-1, 1), 0);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}