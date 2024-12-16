
#include <iostream>
#include "testing.h"

TEST(BraneScript, EmptyPlaceholder)
{
    std::cout << "Hello world!" << std::endl;
    EXPECT_TRUE(true);
}

TEST(BraneScript, LawsOfMathStillWork)
{
    std::cout << "Hello world!" << std::endl;
    EXPECT_EQ(2 + 2, 4);
}
