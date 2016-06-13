#include <limits.h>
#include "gtest/gtest.h"

TEST(Pilot, InitialTest){
    ASSERT_TRUE(true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
